#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 10:07:16 AM CST


def get_content():
    return "hello world"


def foo(bar):
    print(bar())
    return bar


if __name__ == "__main__":
    # show
    print("show")
    print(id(get_content))
    print(type(get_content))
    print(get_content)

    # assign
    print("assign")
    func_1 = get_content
    print(func_1())

    # as parameter
    print("as parameter")
    func_2 = foo(get_content)
    print(func_2())
