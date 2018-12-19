#!/usr/bin/env python2
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 15 Aug 2018 12:37:28 PM CST


class A(list):
    def show(self):
        print("A::show")


class B(list):
    def show(self):
        print("B::show")


class C(A):
    pass


class D(C, B):
    pass


d = D()
d.show()
print(D.__mro__)
print(type(D.__mro__))
