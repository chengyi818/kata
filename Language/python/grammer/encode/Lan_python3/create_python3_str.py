#!/usr/bin/env python3

def show(object):
    print("type: ", type(object))
    print("id: ", id(object))
    print("value: ", object)


a = "中"
b = '\u4e2d'
c = b"\xe4\xb8\xad"

show(a)
show(b)
show(c)
