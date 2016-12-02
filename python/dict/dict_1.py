#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: dict_1.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-30 10:52:11
#       Version: 0.0.1
#    LastChange: 2016-11-30 10:52:11
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

DICT_1 = {'Mon': 1, "Tue": 2, "WeekEnd":{'Sat', 'Sun'}}
if 'Sat' in DICT_1['WeekEnd']:
    print "Sat in DICT_1"
else:
    print "Sat not in DICT_1"

DICT_1['Wed'] = 3
print DICT_1

DICT_2 = {'Thur': 4}
# DICT_1 = dict(DICT_1, **DICT_2)
print DICT_1


