#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 11:16:11 AM CST
import functools


def add(num):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            return (func(*args, **kwargs)+num)
        return wrapper
    return decorator


def plus(num):
    def decorator(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            return(func(*args, **kwargs)*num)
        return wrapper
    return decorator


@add(2)
@plus(3)
def show(raw_num):
    return raw_num


if __name__ == "__main__":
    print(show(2))
