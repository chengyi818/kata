#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

# 30x+15y=675
# 12x+5y=265

import z3

x = z3.Real('x')
y = z3.Real('y')  # 设未知数
s = z3.Solver()  # 创建约束求解器
s.add(30*x+15*y == 675)
s.add(12*x+5*y == 265)  # 添加约束条件

if s.check() == z3.sat:  # 检测是否有解
    result = s.model()
    print(result)  # 若有解则得出解，注意这里的解是等式
else:
    print('no result')  # 无解则打印no result
