import json
import socket
import sys

HOST= '127.0.0.1'
PORT = 9999

m ='{"id": 2, "name": "abc"}'

# Create a socket (SOCK_STREAM means a TCP socket)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to server and send data
    sock.connect((HOST, PORT))
    sock.sendall(m)


    # Receive data from the server and shut down
    received = sock.recv(1024)
finally:
    sock.close()