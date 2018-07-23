#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 11 Jan 2018 08:10:05 PM CST

"""
data descriptor 优于 instance属性
"""


class A(list):
    """
    self: class A的实例value
    obj: class B的实例b
    cls: class B
    """
    def __get__(self, obj, cls):
        print("A.__get__")
        print("self", self)
        print("obj", obj)
        print("cls", cls)
        return "A.__get__"

    def __set__(self, obj, value):
        print("A.__set__")
        print("self", self)
        print("obj", obj)
        print("value", value)
        self.append(value)


class B(object):
    value = A()


if __name__ == "__main__":
    b = B()
    b.value = 1
    print(b.__class__.__dict__['value'])
    print(b.__dict__["value"])
