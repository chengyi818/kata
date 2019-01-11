#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 09 Jan 2018 07:32:46 PM CST


# class A(object):
#     print("create A")
#     name = "Python"

#     def __init__(self):
#         print("A::__init__")

#     def f(self):
#         print("A::f")

#     def g(self, input):
#         self.value = input
#         print(self.value)

name = "Python"


def __init__(self):
    print("A::__init__")


def f(self):
    print("A::f")


def g(self, input):
    self.value = input
    print(self.value)


A = type('China', (object,), dict(__init__=__init__, f=f, g=g))


a = A()
print(A.__name__)
a.f()
a.g(10)
