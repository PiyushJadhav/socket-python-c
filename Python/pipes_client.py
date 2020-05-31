import json
import socket
import sys

HOST= '127.0.0.1'
PORT = 9986

m ={'id': 2, 'name': 2}
data = json.dumps(m)

# Create a socket (SOCK_STREAM means a TCP socket)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to server and send data
    sock.connect((HOST, PORT))
    sock.sendall(data.encode(encoding = 'UTF-8',errors = 'strict'))

except TypeError:
    raise Exception('encode() the message as well')

finally:
    data = sock.recv(1024)
    if data:
        data.decode(encoding = 'UTF-8',errors = 'strict')
        data = json.loads(data)
        print(data)
    sock.close()
