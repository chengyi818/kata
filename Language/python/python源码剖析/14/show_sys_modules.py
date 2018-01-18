#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 18 Jan 2018 10:18:47 PM CST
import sys


def show_modules():
    for item in sys.modules.items():
        print(item)


show_modules()
print(id(sys.modules['os']))

import os
print(id(os))

print(dir())
print(os.__file__)
print(__file__)
