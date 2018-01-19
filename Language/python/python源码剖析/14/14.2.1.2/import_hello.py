#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 18 Jan 2018 10:24:35 PM CST
import sys


def containHello():
    return "hello" in sys.modules.keys()


print(containHello())

import hello

print(containHello())
print(dir())
print(id(hello))
print(id(sys.modules['hello']))
