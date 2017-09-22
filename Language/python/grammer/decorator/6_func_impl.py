#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 10:29:02 AM CST


def make_bold(func):
    print('Initialize')

    def wrapper():
        print('Call')
        return '<b>{}</b>'.format(func())
    return wrapper


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
