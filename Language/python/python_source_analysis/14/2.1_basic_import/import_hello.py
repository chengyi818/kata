#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 18 Jan 2018 10:24:35 PM CST
import sys


def containHello():
    return "hello" in sys.modules.keys()


print("containHello: ", containHello())

import hello

print("containHello: ", containHello())
print("dir(): ", dir())
print("id(hello): ", id(hello))
print("id(sys.modules['hello']): ", id(sys.modules['hello']))
