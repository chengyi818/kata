#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: module_y.py
#          Desc: module_y-->module_z
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-26 14:59:47
#       Version: 0.0.1
#    LastChange: 2016-11-26 14:59:48
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
from subpackage2 import module_z
from subpackage2.module_z import ModuleZ

def func_y():
    print "subpackage1-->module_y-->func_y()"

class ModuleY(object):
    def __init__(self):
        self.name = "ModuleY"

    def my_print(self):
        print "subpackage1-->module_Y-->%s" % self.name
        module_z.func_z()
        my_z = ModuleZ()
        my_z.my_print()
