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


def triangles():
    line = [1]
    while True:
        line_pre = line
        yield line
        line = []

        tmp_line = [0]
        for num in line_pre:
            tmp_line.append(num)
        tmp_line.append(0)

        for index, num in enumerate(tmp_line):
            if (index+1) < len(tmp_line):
                current_num = tmp_line[index] + tmp_line[index+1]
                line.append(current_num)
            else:
                break


N = 0
for t in triangles():
    print(t)
    N = N + 1
    if N == 20:
        break
