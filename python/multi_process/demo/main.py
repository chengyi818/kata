#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: demo.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-15 14:41:20
#       Version: 0.0.1
#    LastChange: 2016-11-15 14:41:20
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import multiprocessing
import time
import random
import signal

class SocketProcess(multiprocessing.Process):
    def __init__(self, name, task_queue, result_queue):
        multiprocessing.Process.__init__(self)
        self.task_queue = task_queue
        self.result_queue = result_queue
        self.name = name

    def run(self):
        while True:
            next_task = self.task_queue.get()
            print "%s: testing %s" % (self.name, next_task)
            answer = next_task()
            self.task_queue.task_done()
            self.result_queue.put(answer)

class LogProcess(multiprocessing.Process):
    def __init__(self, name, task_queue, result_queue):
        multiprocessing.Process.__init__(self)
        self.task_queue = task_queue
        self.result_queue = result_queue
        self.name = name

    def run(self):
        while True:
            next_task = self.task_queue.get()
            if next_task.result == -1:
                print "%s: %s start log" % (self.name, next_task.name)
            elif next_task.result == 1:
                print "%s: %s drop log\n" % (self.name, next_task.name)
            elif next_task.result == 0:
                print "%s: %s save log\n" % (self.name, next_task.name)
            self.task_queue.task_done()

class Task(object):
    def __init__(self, name):
        self.name = name
        self.result = -1

    def __call__(self):
        random_time = random.randint(1, 5)
        time.sleep(random_time) # pretend to take some time to do the work
        self.result = random.randint(0, 1) # simulate result True(1) or False(0)
        return self

    def __str__(self):
        return self.name





if __name__ == '__main__':
    def handler_timeout(signum, frame):
        raise AssertionError


    # Establish communication queues with Socket Process
    SOCKET_TASK_QUEUE = multiprocessing.JoinableQueue()
    SOCKET_RESULT_QUEUE = multiprocessing.Queue()

    # Establish communication queues with Socket Process
    LOG_TASK_QUEUE = multiprocessing.JoinableQueue()
    LOG_RESULT_QUEUE = multiprocessing.Queue()

    SOCKET_PROCESS = SocketProcess("socket_process", SOCKET_TASK_QUEUE, SOCKET_RESULT_QUEUE)
    LOG_PROCESS = LogProcess("log_process", LOG_TASK_QUEUE, LOG_RESULT_QUEUE)
    SOCKET_PROCESS.start()
    LOG_PROCESS.start()

    for i in range(10):
        LOG_TASK_QUEUE.put(Task("CVE_"+str(i)))
        SOCKET_TASK_QUEUE.put(Task("CVE_"+str(i)))
        try:
            #start timer
            signal.signal(signal.SIGALRM, handler_timeout)
            signal.alarm(4)

            #wait for test result
            socket_result = SOCKET_RESULT_QUEUE.get()
            if socket_result.result == 1:
                print "MainProcess: %s Patched" % socket_result.name
                #stop timer
                LOG_TASK_QUEUE.put(socket_result)
            elif socket_result.result == 0:
                print "MainProcess: %s Vulnerable" % socket_result.name
                #stop timer
                LOG_TASK_QUEUE.put(socket_result)
            signal.alarm(0)
            time.sleep(1)
        except AssertionError:
            time.sleep(3)
            socket_result = SOCKET_RESULT_QUEUE.get()
            print "handle timeout Case\n"


    SOCKET_TASK_QUEUE.join()
    LOG_PROCESS.terminate()
    SOCKET_PROCESS.terminate()
