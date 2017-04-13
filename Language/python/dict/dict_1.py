#!/usr/bin/env python
# -*- coding: UTF-8 -*-

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
