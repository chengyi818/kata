#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 09 Jan 2018 07:32:46 PM CST


class A(object):
    print("create A")
    name = "Python"

    def __init__(self):
        print("A::__init__")

    def f(self):
        print("A::f")

    def g(self, input):
        self.value = input
        print(self.value)


a = A()
# a.f()
# a.g(10)

# print(a.__class__.__dict__['f'])
print(a.f)
a.f()

print(A.f)

a.f = 2
print(a.f)
print(A.f)
