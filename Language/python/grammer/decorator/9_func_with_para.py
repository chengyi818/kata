#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 21 Sep 2017 11:11:02 AM CST


class make_bold(object):
    def __init__(self, func):
        self.func = func

    def __call__(self, *args, **kwargs):
        return '<b>{}</b>'.format(self.func(*args, **kwargs))


@make_bold
def get_login_tip(name):
    return 'Welcome back, {}'.format(name)


if __name__ == "__main__":
    print(get_login_tip("Eason"))
