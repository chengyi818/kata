#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: create_class_as_single_process.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-14 15:04:33
#       Version: 0.0.1
#    LastChange: 2016-11-14 15:04:33
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

class ClockProcess(multiprocessing.Process):
    def __init__(self, interval):
        multiprocessing.Process.__init__(self)
        self.interval = interval

    def run(self):
        n = 100
        while n > 0:
            print("the time is {0}".format(time.ctime()))
            time.sleep(self.interval)
            n -= 1

if __name__ == '__main__':
    p = ClockProcess(3)
    p.start()
    time.sleep(10)
    p.terminate()
