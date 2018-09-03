#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 03 Sep 2018 01:54:35 PM CST

import threading
import time


class MyThread(threading.Thread):
    def run(self):
        while True:
            print("subthread: ", threading.get_ident())
            time.sleep(2)


mythread = MyThread()
mythread.start()
while True:
    print("main thread: ", threading.get_ident())
    time.sleep(2)
