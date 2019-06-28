#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 28 Jun 2019 09:15:33 AM CST


# 例1
def foo():
    exec('y = 1 + 1')
    y = locals()['y']
    print(y)


foo()

# 报错：KeyError: 'y'
