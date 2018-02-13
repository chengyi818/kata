#!/usr/bin/env python2
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 13 Feb 2018 12:31:15 PM CST
import gc


class A(object):
    pass


class B(object):
    pass


gc.set_debug(gc.DEBUG_STATS | gc.DEBUG_LEAK)
a = A()
b = B()
del a
del b
gc.collect()
