#!/usr/bin/env python3

def show(object):
    print("type: ", type(object))
    print("id: ", id(object))
    print("value: ", object)


a = "中"
b = '\u4e2d'
c = '\U00004e2d'
d = "\N{CJK UNIFIED IDEOGRAPH-4E2D}"

show(a)
show(b)
show(c)
show(d)
