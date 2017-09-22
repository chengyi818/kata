#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 10:14:48 AM CST


class FuncObj(object):
    def __init__(self, name):
        print('Initialize')
        self.name = name

    def __call__(self):
        print('Hi', self.name)


if __name__ == "__main__":
    foo = FuncObj("python")
    foo()
