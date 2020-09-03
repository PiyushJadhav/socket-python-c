This repository is to setup a dummy communication between the Python and C process using IPC sockets to send json formatted strings.

In this Server-Client mode of the communication, both C and Python has its own server and client. These files can be used to send messages across server and client process. 

To use this application, you need to open two terminals inside a particular subfolder:
1. Compile the C program using gcc, 
    `gcc $(pkg-config --cflags json-glib-1.0) server.c -o server $(pkg-config --libs json-glib-1.0)`
        OR
    `gcc $(pkg-config --cflags json-glib-1.0) client.c -o client $(pkg-config --libs json-glib-1.0)`
2. In the first terminal, Run the server application
    `python server.py`
        OR
    `./server`
3. In the second terminal, Run the client application,
    `python client.py`
        OR
    `./client`
4. Enjoy IPC!
