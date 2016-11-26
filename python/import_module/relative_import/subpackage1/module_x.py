#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: module_x.py
#          Desc: module_x-->module_y
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-26 14:58:11
#       Version: 0.0.1
#    LastChange: 2016-11-26 14:58:11
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

from . import module_y
from subpackage1.module_y import ModuleY

def func_x():
    print "subpackage1-->module_x-->func_x()"

class ModuleX(object):
    def __init__(self):
        self.name = "ModuleX"

    def my_print(self):
        print "subpackage1-->module_x-->%s" % self.name
        module_y.func_y()
        my_y = ModuleY()
        my_y.my_print()


