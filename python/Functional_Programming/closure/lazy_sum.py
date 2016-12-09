#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: lazy_sum.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-09 10:23:36
#       Version: 0.0.1
#    LastChange: 2016-12-09 10:23:36
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

def lazy_sum(*args):
    def my_sum():
        ax = 0
        for n in args:
            ax = ax + n
        return ax
    return my_sum

f1 = lazy_sum(1, 3, 5)
f2 = lazy_sum(1, 3, 5, 7)

print f1()
print f2()
