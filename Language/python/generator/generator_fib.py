#!/usr/bin/env python3
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


def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a+b
        n += 1


f = fib(6)
for x in f:
    print(x)
