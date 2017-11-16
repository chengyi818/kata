#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 16 Nov 2017 03:09:19 PM CST


def foo(s):
    """
    >>> foo(5)
    2
    >>> foo(3)
    4
    """
    n = int(s)
    assert n != 0, "n is 0!"
    return 10 / n


def test_foo():
    assert foo(2) == 5
    assert foo(3) == 3


def main():
    import doctest
    doctest.testmod()


main()
