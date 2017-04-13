#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: block.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-15 10:41:44
#       Version: 0.0.1
#    LastChange: 2016-11-15 10:41:44
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

def func(msg):
    print "msg:", msg
    time.sleep(3)
    print "end"

if __name__ == "__main__":
    pool = multiprocessing.Pool(processes = 3)
    for i in xrange(4):
        msg = "hello %d" %(i)
        pool.apply(func, (msg, ))   #维持执行的进程总数为processes，当一个进程执行完毕后会添加新的进程进去

    print "Mark~ Mark~ Mark~~~~~~~~~~~~~~~~~~~~~~"
    pool.close()
    pool.join()   #调用join之前，先调用close函数，否则会出错。执行完close后不会有新的进程加入到pool,join函数等待所有子进程结束
    print "Sub-process(es) done."
