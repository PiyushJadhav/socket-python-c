/**
 * @file client.c
 * @brief This file create a client-socket process which sends and receives json data.
 * @note This module uses json-glib library to build json messages in C and to compile with GCC see the readme for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <json-glib/json-glib.h>
#include <json-glib/json-gobject.h>

int main()
{
    //setup
    int localPort = 5001;
    int ourClientSocket;
    struct sockaddr_in serverAddress;
    char buffToReceive[512];
    gchar *buffToSend;

    // building json string
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object(builder);
    json_builder_set_member_name(builder, "Client side");
    json_builder_add_string_value(builder, "C process");
    json_builder_set_member_name(builder, "Connecting to port:");
    json_builder_begin_array(builder);
    json_builder_add_int_value(builder, localPort);
    json_builder_end_array(builder);
    json_builder_end_object(builder);
    JsonGenerator *gen = json_generator_new();
    JsonNode * root = json_builder_get_root( builder );
    json_generator_set_root( gen, root );
    buffToSend = json_generator_to_data(gen, NULL);
    printf("Sending from C client: %s \n", buffToSend);

    printf("Starting C process Client\n");
    //create a socket with name
    ourClientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(ourClientSocket == -1)
    {
        printf("Socket err \n");
        exit(1);
    }

    //connect
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; //Any local address, but could be configured for 127.0.0.0
    serverAddress.sin_port = htons(localPort);

    if(connect(ourClientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
    {
        printf("Connect error \n");
        close(ourClientSocket);
        exit(1);
    }

    // Sends and Receive data
    // send
    if(write(ourClientSocket, buffToSend, strlen(buffToSend)) == -1)
    {
        printf("Send error\n");
        close(ourClientSocket);
        exit(1);
    }

    // recv
    if(read(ourClientSocket, buffToReceive, sizeof(buffToReceive)) == -1)
    {
        printf("Recv error \n");
        close(ourClientSocket);
        exit(1);
    }
    printf("Received data from server %s\n",buffToReceive);

    //close socket
    printf("Now closing socket \n");
    close(ourClientSocket);

    json_node_free (root);
    g_object_unref (gen);
    g_object_unref (builder);
    return 0;
}