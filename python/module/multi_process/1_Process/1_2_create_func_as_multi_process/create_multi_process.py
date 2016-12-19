#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: create_multi_process.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-14 14:51:08
#       Version: 0.0.1
#    LastChange: 2016-11-14 14:51:08
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

def worker_1(interval):
    print ("worker_1")
    time.sleep(interval)
    print ("end worker_1")

def worker_2(interval):
    print ("worker_2")
    time.sleep(interval)
    print ("end worker_2")

def worker_3(interval):
    print ("worker_3")
    time.sleep(interval)
    print ("end worker_3")

if __name__ == "__main__":
    p1 = multiprocessing.Process(target = worker_1, name = "socket", args = (2,))
    p2 = multiprocessing.Process(target = worker_2, args = (3,))
    p3 = multiprocessing.Process(target = worker_3, args = (4,))

    p1.start()
    p2.start()
    p3.start()

    print("The number of CPU is:" + str(multiprocessing.cpu_count()))
    for p in multiprocessing.active_children():
        print("child   p.name:" + p.name + "\tp.id" + str(p.pid))
    print ("END!!!!!!!!!!!!!!!!!")
