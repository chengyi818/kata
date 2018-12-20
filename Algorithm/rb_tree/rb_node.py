#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 08:58:22 PM CST
BLACK = 'grey'
RED = 'red'
NULL = 'Nil'


class RbNode(object):
    def __init__(self, value, color=RED):
        self.color = color
        self.value = value
        self.parent = None
        if(value != NULL):
            self.left = RbNode(NULL, BLACK)
            self.right = RbNode(NULL, BLACK)
        else:
            self.left = None
            self.right = None

    def set_red(self):
        self.color = RED

    def set_black(self):
        self.color = BLACK

    def is_black(self):
        if(self.color == BLACK):
            return True
        else:
            return False

    def is_red(self):
        if(self.color == RED):
            return True
        else:
            return False

    def get_uncle(self):
        grandparent = self.get_grandparent()
        if(grandparent):
            if(self.parent == grandparent.left):
                return grandparent.right
            else:
                return grandparent.left
        return None

    def get_grandparent(self):
        parent = self.parent
        if(parent):
            return parent.parent
        else:
            return None
