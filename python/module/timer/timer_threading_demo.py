#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import threading
import socket
import queue
import time

class ReceiveThread(threading.Thread):
    def __init__(self, sock, tmp_queue):
        threading.Thread.__init__(self)
        self.sock = sock
        self.tmp_queue = tmp_queue

    def run(self):
        self.sock.sendall('hello'.encode())
        time.sleep(6)
        # data = self.sock.recv(8096).decode()
        self.tmp_queue.put('world')
        print("ReceiveThread end")

class ControlThread(threading.Thread):
    def __init__(self, sock, my_queue, time_out):
        threading.Thread.__init__(self)
        self.sock = sock
        self.my_queue = my_queue
        self.time_out = time_out

    def run(self):
        tmp_queue = queue.Queue(1)
        receive_thread = ReceiveThread(self.sock, tmp_queue)
        receive_thread.setDaemon(True)
        receive_thread.start()

        receive_thread.join(self.time_out)
        try:
            tmp_data = tmp_queue.get(block=False)
        except queue.Empty:
            self.my_queue.put([])
        else:
            self.my_queue.put(tmp_data)


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 8888))
    my_queue = queue.Queue(1)

    control_thread = ControlThread(sock, my_queue, 5)
    control_thread.start()
    data = my_queue.get(block=True)
    if data:
        print("receive data: ", data)
    else:
        print("timeout")



if __name__ == "__main__":
    main()
