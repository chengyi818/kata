#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: singleton_module.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-12 22:58:45
#       Version: 0.0.1
#    LastChange: 2016-12-12 22:58:45
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

count = [0]

def increase_count():
    count[0] += 1

def decrease_count():
    count[0] -= 1

def print_count():
    print "count: {0}".format(count[0])

