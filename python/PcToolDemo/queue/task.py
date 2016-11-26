#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: task.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-23 15:00:39
#       Version: 0.0.1
#    LastChange: 2016-11-23 15:00:39
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import time
import random

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
