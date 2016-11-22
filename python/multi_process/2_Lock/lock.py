#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: lock.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-14 15:45:08
#       Version: 0.0.1
#    LastChange: 2016-11-14 15:45:08
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

def worker_with(lock, f):
    with lock:
        fs = open(f, 'a+')
        n = 10
        while n > 1:
            fs.write("Lockd acquired via with\n")
            n -= 1
        fs.close()

def worker_no_with(lock, f):
    lock.acquire()
    try:
        fs = open(f, 'a+')
        n = 10
        while n > 1:
            fs.write("Lock acquired directly\n")
            n -= 1
        fs.close()
    finally:
        lock.release()

if __name__ == "__main__":
    lock = multiprocessing.Lock()
    f = "file.txt"
    fs = open(f, 'w')
    fs.close()

    w = multiprocessing.Process(target = worker_with, args=(lock, f))
    nw = multiprocessing.Process(target = worker_no_with, args=(lock, f))
    w.start()
    nw.start()

    time.sleep(2)
    with lock:
        for line in open("file.txt"):
            print (line)
