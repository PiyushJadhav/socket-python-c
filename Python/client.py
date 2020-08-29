#!/usr/bin/env python
import socket
import sys
import random
import json

localPort = 5001
localHost = "127.0.0.1"
buffSize = 512

# json struct
dictClient = {
        'Client side':[localHost,localPort],
        'Process':"Python3"
    }

def startClient():
    # socket creating using module
    serverAddr = (localHost, localPort)
    try:
        ourSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # setup
        ourSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except:
        ourSocket = None
        print("ERROR: Creating socket failed")

    # connect to server side
    try:
        ourSocket.connect(serverAddr)
        print("Connected to %s" % repr(serverAddr))
    except:
        print("ERROR: Connection to %s refused" % repr(serverAddr))
        sys.exit(1)

    # send
    try:
        jsonClient = json.dumps(dictClient)
        bytesToSend = jsonClient.encode('utf-8')
        ourSocket.sendall(bytesToSend)
        print("Sending from client side: ", bytesToSend)
        
        # receive
        buffReceived = ourSocket.recv(buffSize)
        jsonReceived = json.loads(buffReceived)
        print("Received json format message: ", jsonReceived)

    # close
    finally:
        print ("Closing socket")
        ourSocket.close()

if __name__ == "__main__":
    startClient()