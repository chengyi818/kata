#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: log_process.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-23 14:59:44
#       Version: 0.0.1
#    LastChange: 2016-11-23 14:59:44
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

import multiprocessing

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
