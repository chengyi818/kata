#!/usr/bin/env python3
# encoding=utf-8

def swap(a, b):
    print("locals in swap before swap: ", locals())
    tmp = a
    a = b
    b = tmp
    print("locals in swap after swap: ", locals())

print("locals in global before swap: ", locals())
print("globals in global before swap: ", globals())
a = 1
b = 2
swap(a, b)
print("locals in global after swap: ", locals())
print("globals in global after swap: ", globals())
