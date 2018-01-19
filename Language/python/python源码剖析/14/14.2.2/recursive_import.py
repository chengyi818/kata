#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 19 Jan 2018 12:05:08 PM CST

print(dir())
import sys

import usermodule1

print(dir())
print(dir(usermodule1))
print(dir(usermodule1.usermodule2))


print(sys.modules.keys())
