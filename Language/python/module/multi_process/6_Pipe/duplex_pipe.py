#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: my_pipe.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-15 10:16:56
#       Version: 0.0.1
#    LastChange: 2016-11-15 10:16:56
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time

def proc1(pipe):
    while True:
        for i in range(10):
            print ("send: %s" %(i))
            pipe.send(i)
            time.sleep(1)

def proc2(pipe):
    while True:
        print ("proc2 rev:", pipe.recv())
        time.sleep(1)

if __name__ == "__main__":
    pipe = multiprocessing.Pipe(duplex=False)
    p1 = multiprocessing.Process(target=proc1, args=(pipe[1],))
    p2 = multiprocessing.Process(target=proc2, args=(pipe[0],))

    p1.start()
    p2.start()

    p1.join()
    p2.join()
