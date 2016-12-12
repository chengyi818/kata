#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: singleton_1.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-12 21:47:20
#       Version: 0.0.1
#    LastChange: 2016-12-12 21:47:20
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

class Singleton(object):
    _instance = None
    def __new__(cls, *args, **kwargs):
        if not cls._instance:
            cls._instance = super(Singleton, cls).__new__(cls, *args, **kwargs)

        return cls._instance

if __name__ == '__main__':
    s1 = Singleton()
    s2 = Singleton()
    if id(s1) == id(s2):
        print "id(s1) == id(s2)"

