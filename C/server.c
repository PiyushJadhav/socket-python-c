/**
 * @file server.c
 * @brief This file create a server-socket process which sends and receives json data.
 * @note This module uses json-glib library to build json messages in C and to compile with GCC see the readme for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <json-glib/json-glib.h>
#include <json-glib/json-gobject.h>

int main()
{
    int localPort = 5001;
    char buffToReceive[512];
    int ourSocket, clientSocket;
    struct sockaddr_in serverAddress, client;
    int clilen = sizeof( client );
    gchar *buffToSend;

    // building json string
    JsonBuilder *builder = json_builder_new();
    json_builder_begin_object( builder );
    json_builder_set_member_name( builder, "Server side" );
    json_builder_add_string_value( builder, "C process" );
    json_builder_set_member_name( builder, "Connecting to port:" );
    json_builder_begin_array( builder );
    json_builder_add_int_value( builder, localPort );
    json_builder_end_array( builder );
    json_builder_end_object( builder );
    JsonGenerator *gen = json_generator_new();
    JsonNode * root = json_builder_get_root( builder );
    json_generator_set_root( gen, root );
    buffToSend = json_generator_to_data ( gen, NULL );
    printf( "Sending from C client: %s \n", buffToSend );

    // create socket
    ourSocket = socket( AF_INET, SOCK_STREAM, 0 );
    // reusable socket set
    setsockopt( ourSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int) );
    
    printf( "Server listening on port %d\n", localPort );

    // bind to local memory
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons( localPort );
    if( bind( ourSocket, ( struct sockaddr * )&serverAddress , sizeof( serverAddress )) < 0 )
    {
        printf("ERROR: Bind failed\n");
        exit(1);
    }

    // listen
    listen( ourSocket , 3 );

    if( clientSocket = accept( ourSocket, ( struct sockaddr * ) &client, &clilen ))
    {
        // receive json string
        read( clientSocket, buffToReceive, sizeof( buffToReceive ));
        printf( "Received data: %s \n", buffToReceive );
        
        // sends json data
        write( clientSocket, buffToSend, strlen( buffToSend ));
        printf( "sent\n" );
    }
    else
    {
       printf( "Error: accept() failed\n" );
    }
    

    // close
    printf( "Now Closing socket\n" );
    close( ourSocket );
    
    return 0;
}