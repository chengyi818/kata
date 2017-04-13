#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: partial.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-09 10:59:38
#       Version: 0.0.1
#    LastChange: 2016-12-09 10:59:38
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
import functools

int2 = functools.partial(int, base=2)
max2 = functools.partial(max, 10)

print int2('1000000')
print int2('1000000', base=10)

print max2(5, 6, 7)
