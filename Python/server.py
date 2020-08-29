#!/usr/bin/env python
# server.py


import socket
import sys
import traceback
import json

localPort = 5001
localHost = "127.0.0.1"
buffSize = 512

# json struct
dictServer = {
        'Server':[localHost,localPort],
        'Process':"Python3"
    }

def startServer():

    serverAddr = (localHost, localPort)
    try:
        # Socket creation using module
        ourSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # setup
        ourSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except:
        ourSocket = None
        print("could not setup socket")

    # Socket bind
    ourSocket.bind(serverAddr)

    # listen
    ourSocket.listen()

    # accept
    connected, addr = ourSocket.accept()

    # receive
    try:
        with connected:
            jsonServer = json.dumps(dictServer)
            bytesToSend = jsonServer.encode('utf-8')

            while True:
                # received string
                stringReceived = connected.recv(buffSize)
                if not stringReceived:
                    break
                print("Received: ", stringReceived)
                # send json
                print('Sending from Server python as Bytes: ',bytesToSend)
                connected.sendall(bytesToSend)

    except TypeError:
        print("TypeError: Error occurred while execution")

    finally:
        # close the socket connection
        print("Closing socket")
        ourSocket.close()

if __name__ == "__main__":
    startServer()