#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 08:58:22 PM CST
BLACK = 'grey'
RED = 'red'

class RbNode(object):
    def __init__(self, value, color=RED):
        self.color = color
        self.value = value
        self.parent = None
        self.left = None
        self.right = None
