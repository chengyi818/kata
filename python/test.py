#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: test.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-05-09 15:58:38
#       Version: 0.0.1
#    LastChange: 2016-05-09 16:14:08
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
a,b = 0,1
while b < 10:
    print(b)
    a, b = b, a+b
