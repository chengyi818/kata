#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 10:44:00 AM CST


def outer():
    msg = 'hello world'

    def inner():
        print(msg)
    return inner


if __name__ == "__main__":
    func = outer()
    func()
