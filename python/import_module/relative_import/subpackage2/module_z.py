#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: module_z.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-26 15:01:52
#       Version: 0.0.1
#    LastChange: 2016-11-26 15:01:52
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

def func_z():
    print("subpackage2-->module_z-->func_z()")

class ModuleZ(object):
    def __init__(self):
        self.name = "ModuleZ"

    def my_print(self):
        print("subpackage2-->module_Z-->%s" % self.name)
