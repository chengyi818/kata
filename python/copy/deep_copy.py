#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: deep_copy.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-06 10:17:03
#       Version: 0.0.1
#    LastChange: 2016-12-06 10:17:03
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

import copy

def my_print(obj):
    print id(obj)
    print obj
    print [id(ele) for ele in obj]
    print "\n"


will = ["Will", 28, ["Python", "C++", "C"]]
wilber = copy.deepcopy(will)

my_print(will)
my_print(wilber)

will[0] = "Wilber"
will[2].append("Java")
my_print(will)
my_print(wilber)
