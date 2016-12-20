#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import threading
import socket
import queue

class ReceiveThread(threading.Thread):
    def __init__(self, sock, my_queue):
        threading.Thread.__init__(self)
        self.sock = sock
        self.my_queue = my_queue

    def run(self):
        self.sock.sendall('hello'.encode())
        data = self.sock.recv(8096).decode()
        self.my_queue.put(data)



def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 8888))
    my_queue = queue.Queue(1)

    receive_thread = ReceiveThread(sock, my_queue)
    receive_thread.start()
    try:
        data = my_queue.get(block=True, timeout=5)
    except queue.Empty:
        # if receive_thread.is_alive():
            # receive_thread.terminate()

        print("timeout")

    if data:
        print("receive data: ", data)



if __name__ == "__main__":
    main()
