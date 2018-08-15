#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 09 Aug 2018 08:08:06 PM CST


class A(object):
    def __init__(self):
        print("__init__ A")
        self.a = "a"


class B(A):
    def __init__(self):
        super().__init__()
        print("__init__ B")
        self.b = "b"


b = B()
