#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: test.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-06 10:24:32
#       Version: 0.0.1
#    LastChange: 2016-12-08 19:00:08
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

def normalize(numbers):
    total = sum(numbers)
    result = []
    for value in numbers:
        percent = 100 * value/total
        result.append(percent)
    return result

def ReadVisits(object):
    def __init__(self, data_path):
        print self.data_path
        self.data_path = data_path

    def __iter__(self):
        with open(self.data_path) as f:
            for line in f:
                yield int(line)


visits = ReadVisits('my_numbers')
percetanges = normalize(visits)
print percetanges
