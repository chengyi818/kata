#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Sun 19 May 2019 09:21:02 PM CST

head, *body, tail = range(5)
print(head, body, tail)
# 0 [1, 2, 3] 4
py, filename, *cmds = "python3.7 script.py -n 5 -l 15".split()
print(py)
print(filename)
print(cmds)
# python3.7
# script.py
# ['-n', '5', '-l', '15']
first, _, third, *_ = range(10)
print(first, third)
# 0 2
