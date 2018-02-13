#!/usr/bin/env python2
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 13 Feb 2018 12:35:55 PM CST
import gc


class A(object):
    def __del__(self):
        pass


class B(object):
    def __del__(self):
        pass


gc.set_debug(gc.DEBUG_STATS | gc.DEBUG_LEAK)
a = A()
b = B()
a.b = b
b.a = a
del a
del b
gc.collect()
