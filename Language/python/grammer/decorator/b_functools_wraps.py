#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 01:59:17 PM CST

import functools


def make_bold(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return '<b>{}</b>'.format(func(*args, **kwargs))
    return wrapper


def make_bold2(func):
    def wrapper(*args, **kwargs):
        return '<b>{}</b>'.format(func(*args, **kwargs))
    return wrapper


@make_bold
def get_content():
    return 'hello world'


@make_bold2
def get_content2():
    return 'hello world'


if __name__ == "__main__":
    print(get_content.__name__)

    print(get_content2.__name__)
