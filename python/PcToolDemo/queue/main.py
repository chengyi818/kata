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
import signal
import commands
from socket_process import SocketProcess
from log_process import LogProcess
from task import Task


if __name__ == '__main__':
    def handler_timeout(signum, frame):
        # pylint: disable=unused-argument
        raise AssertionError

    def adb_forward():
        cmd = 'adb forward tcp:11010 tcp:42178'
        (status, _) = commands.getstatusoutput(cmd)
        if status == 0:
            print "adb forward success\n"
            return True
        else:
            print "adb forward fail\n"
            return False


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

    # adb forward
    # adb_forward()

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
                LOG_TASK_QUEUE.put(socket_result)
            elif socket_result.result == 0:
                print "MainProcess: %s Vulnerable" % socket_result.name
                LOG_TASK_QUEUE.put(socket_result)
            signal.alarm(0)
            time.sleep(1)
        except AssertionError:
            time.sleep(2)
            socket_result = SOCKET_RESULT_QUEUE.get()
            print "handle timeout Case\n"


    SOCKET_TASK_QUEUE.join()
    LOG_PROCESS.terminate()
    SOCKET_PROCESS.terminate()
