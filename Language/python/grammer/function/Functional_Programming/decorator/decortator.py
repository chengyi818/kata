#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: decortator.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-09 10:45:07
#       Version: 0.0.1
#    LastChange: 2016-12-09 10:45:07
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
from functools import wraps

def my_log(func):
    @wraps(func)
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        return func(*args, **kw)
    return wrapper

@my_log
def now():
    print("now")

now()
print(now)
