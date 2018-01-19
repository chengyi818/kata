#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 11 Jan 2018 03:08:08 PM CST


import sys
import time

for i in range(5):
    # 清空之前的输出
    sys.stdout.write(" " * 80 + "\r")
    sys.stdout.flush()  # 输出信息刷新到标准输出

    normal_info = i
    print(i)

    bottom_info = str(i) * (5-i)
    sys.stdout.write(bottom_info)  # 信息输出行
    sys.stdout.write("\r")  # 光标返回行首
    sys.stdout.flush()  # 输出信息刷新到标准输出
    time.sleep(1)
