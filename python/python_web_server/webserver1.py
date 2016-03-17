#!/usr/bin/env python

#  using python 2.7

import socket
import json

HOST, PORT = '', 8888

listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
listen_socket.bind((HOST, PORT))
listen_socket.listen(1)
print 'Serving HTTP on port %s ...' % PORT
while True:
    client_connection, client_address = listen_socket.accept()
    request = client_connection.recv(1024)
    print request
    print client_address

    json_reponse = {'type':'install', "serial":121, 'package':['ubus_example']}
    #  json_reponse = {'type':'install','package':'helloworld'}
    encoded_json = json.dumps(json_reponse)
    print json_reponse

    client_connection.sendall(encoded_json)
    client_connection.close()
