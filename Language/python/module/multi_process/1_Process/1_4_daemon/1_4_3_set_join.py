#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: set_join.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-14 16:35:35
#       Version: 0.0.1
#    LastChange: 2016-11-14 16:35:35
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

def worker(interval):
    print("work start:{0}".format(time.ctime()));
    time.sleep(interval)
    print("work end:{0}".format(time.ctime()));

if __name__ == "__main__":
    p = multiprocessing.Process(target = worker, args = (3,))
    p.daemon = True
    p.start()
    p.join()
    print ("end!")
