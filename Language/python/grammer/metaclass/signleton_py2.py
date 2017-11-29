#!/usr/bin/env python2
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 28 Nov 2017 02:52:07 PM CST


class Singleton(type):
    def __init__(cls, name, bases, dict):
        print("Singleton __init__")
        super(Singleton, cls).__init__(name, bases, dict)
        cls.instance = None

    def __call__(cls, *args, **kwargs):
        if cls.instance is None:
            print("creating a new instance")
            cls.instance = super(Singleton, cls).__call__(*args, **kwargs)
        else:
            print("warning: only one instance can create")

        return cls.instance


class MySignleton(object):
    __metaclass__ = Singleton


if __name__ == "__main__":
    a = MySignleton()
    b = MySignleton()
