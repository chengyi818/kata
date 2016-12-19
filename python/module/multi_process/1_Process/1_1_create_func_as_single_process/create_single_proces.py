#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: create_single_proces.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-14 14:29:38
#       Version: 0.0.1
#    LastChange: 2016-11-14 14:29:38
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time
import os

def worker(interval):
    n = 5
    while n > 0:
        print("child: The time is {0}".format(time.ctime()))
        time.sleep(interval)
        n -= 1

if __name__ == "__main__":
    interval = 3

    print ("father pid:", os.getpid())
    child = multiprocessing.Process(target = worker, args = (interval,))
    child.start()
    print ("child.pid:", child.pid)
    print ("child.name:", child.name)
    print ("child.is_alive:", child.is_alive())

    n = 5
    while n > 0:
        print("father: The time is {0}".format(time.ctime()))
        time.sleep(interval)
        n -= 1
