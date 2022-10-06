#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: singleton_module.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-12 22:58:45
#       Version: 0.0.1
#    LastChange: 2016-12-12 22:58:45
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''


class Counter():
    """
    Counter description
    """

    def __init__(self, name, size):
        self.name = name
        self.size = size

    def print_size(self):
        print("size: {0}".format(self.size))

    def increase_size(self):
        self.size += 1

    def decrease_size(self):
        self.size -= 1


COUNTER = Counter('test', 0)


def increase_count():
    COUNTER.increase_size()


def decrease_count():
    COUNTER.decrease_size()


def print_count():
    COUNTER.print_size()
