#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 11:05:11 AM CST


class decorator(object):
    def __init__(self, make_header2, func):
        self.make_header2 = make_header2
        self.func = func

    def __call__(self):
        return '<h{0}>{1}</h{0}>'.format(self.make_header2.level, self.func())


class make_header2(object):
    def __init__(self, level):
        self.level = level

    def __call__(self, func):
        return decorator(self, func)


def get_content():
    return "hello world"


@make_header2(2)
def get_content2():
    return "hello world"


if __name__ == "__main__":
    tmp_decorator = make_header2(2)
    get_content = tmp_decorator(get_content)
    print(get_content())

    print(get_content2())
