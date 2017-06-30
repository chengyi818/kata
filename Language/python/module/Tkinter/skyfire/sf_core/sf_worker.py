#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 20 Jun 2017 07:50:28 PM CST
import time
import threading
from sf_gui import sf_register


class SfWorker(threading.Thread):
    def __init__(self):
        super(SfWorker, self).__init__()
        self.stopped = False

    def run(self):
        def target_func():
            sf_register.text_mid_right_insert("test begin")
            time.sleep(5)
            sf_register.text_mid_right_insert("test end")

        subthread = threading.Thread(target=target_func, args=())
        subthread.setDaemon(True)
        subthread.start()

        while not self.stopped:
            subthread.join(1)

        sf_register.text_mid_right_insert('Thread stopped')

    def stop(self):
        self.stopped = True

    def isStopped(self):
        return self.stopped
