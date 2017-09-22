#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 10:18:32 AM CST


class make_bold(object):
    def __init__(self, func):
        print('Initialize', func.__name__)
        self.func = func

    def __call__(self):
        print('Call', self.func.__name__)
        return '<b>{}</b>'.format(self.func())


def get_content():
    return "hello world"


@make_bold
def get_content2():
    return "hello world"


if __name__ == "__main__":
    get_content = make_bold(get_content)
    print(type(get_content))
    print(get_content())

    print(get_content2())
    print(type(get_content2))
