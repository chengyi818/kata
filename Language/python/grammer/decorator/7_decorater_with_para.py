#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 10:52:47 AM CST


def make_header(level):
    print('Initialize')

    def decorator(func):
        def wrapper():
            print('Call')
            return '<h{0}>{1}</h{0}>'.format(level, func())
        return wrapper

    return decorator


def get_content():
    return "hello world"


@make_header(2)
def get_content2():
    return "hello world"


if __name__ == "__main__":
    tmp_decorator = make_header(2)
    get_content = tmp_decorator(get_content)
    print(get_content())

    print(get_content2())
