#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import socket

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 8888))

    sock.settimeout(5)
    try:
        sock.sendall('hello'.encode())
        data = sock.recv(8096).decode()
        sock.settimeout(None)
    except socket.timeout:
        print("timeout")
    else:
        if data:
            print("receive data: ", data)
        else:
            print("no data")


if __name__ == "__main__":
    main()
