#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 28 Jun 2019 09:13:49 AM CST
# 例0


def foo():
    exec('y = 1 + 1')
    z = locals()['y']
    print(z)


foo()

# 输出：2
