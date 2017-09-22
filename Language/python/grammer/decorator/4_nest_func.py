#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 10:32:54 AM CST


def outer():
    print('Before def:', locals())

    def inner():
        pass

    print('After def:', locals())
    return inner


if __name__ == "__main__":
    outer()
