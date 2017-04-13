#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: Semaphore.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-14 15:59:22
#       Version: 0.0.1
#    LastChange: 2016-11-14 15:59:22
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

def worker(s, i):
    s.acquire()
    print(multiprocessing.current_process().name + "acquire");
    time.sleep(i)
    print(multiprocessing.current_process().name + "release\n");
    s.release()

if __name__ == "__main__":
    s = multiprocessing.Semaphore(2)
    for i in range(5):
        p = multiprocessing.Process(target = worker, args=(s, i*2))
        p.start()
