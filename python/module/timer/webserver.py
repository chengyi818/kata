#!/usr/bin/env python3


import socket
import random
import time

HOST, PORT = '', 8888

listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listen_socket.bind((HOST, PORT))
listen_socket.listen(1)
print('Serving HTTP on port %s ...' % PORT)
while True:
    client_connection, client_address = listen_socket.accept()
    request = client_connection.recv(1024)
    random_time = random.randint(0, 7)
    print(request)
    print("random_time: ", random_time)
    print(client_address, "\n")


    time.sleep(random_time)

    client_connection.sendall("world".encode())
    client_connection.close()
