#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: Queue.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-14 17:20:39
#       Version: 0.0.1
#    LastChange: 2016-11-14 17:20:39
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

def writer_proc(q):
    try:
        q.put(1)
    except:
        pass

def reader_proc(q):
    try:
        print (q.get())
    except:
        pass

if __name__ == "__main__":
    q = multiprocessing.Queue()

    writer = multiprocessing.Process(target=writer_proc, args=(q,))
    writer.start()

    reader = multiprocessing.Process(target=reader_proc, args=(q,))
    reader.start()

    # reader.join()
    # writer.join()
    # print ("hello world")
    # time.sleep(5)
