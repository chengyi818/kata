#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 28 Nov 2017 03:42:21 PM CST


print("create class Meta")


class Meta(type):
    def __new__(meta, name, bases, class_dict):
        print("Meta __new__")
        print((meta, name, bases, class_dict))
        return type.__new__(meta, name, bases, class_dict)

    def __init__(meta, name, bases, class_dict):
        print("Meta __init__")
        return type.__init__(meta, name, bases, class_dict)

    def __call__(cls, *args, **kwargs):
        print("Meta __call__")
        # instance = super().__call__(*args, **kwargs)
        print(id(cls))
        instance = type.__call__(cls, *args, **kwargs)
        return instance


print("create class MyClass")


class MyClass(object, metaclass=Meta):
    stuff = 123

    def foo(self):
        print("foo")


if __name__ == "__main__":
    print("__main__")
    print(id(MyClass))
    a = MyClass()
    a.foo()
