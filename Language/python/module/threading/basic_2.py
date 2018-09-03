#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 03 Sep 2018 01:54:35 PM CST
from  threading import *
import time


class MyThread(Thread):
    def run(self):
        while True:
            print("subthread: ", current_thread())
            time.sleep(2)


mythread = MyThread()
mythread.start()
while True:
    print("main thread: ", current_thread())
    time.sleep(2)
