#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: state_1.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-12 22:34:43
#       Version: 0.0.1
#    LastChange: 2016-12-12 22:34:43
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

def workday():
    print "work hard!"

def weekend():
    print "play harder"

class People(object):
    pass

if __name__ == "__main__":
    people = People()
    for i in xrange(1, 8):
        if i == 6:
            people.day = weekend
        if i == 1:
            people.day = workday
        people.day()
