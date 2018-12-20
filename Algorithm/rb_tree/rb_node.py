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

    """
    特别说明: 若节点为None,则默认为黑色空节点
    1. 目标节点的父节点和其叔叔节点(祖父节点的另一个子节点)均为红色的;
    """
    def is_need_change_color(self):
        ret = False
        parent = self.parent
        uncle = self.get_uncle()
        if(parent and uncle and parent.is_red() and uncle.is_red()):
            ret = True

        if(ret):
            print("need_change_color: ", self.value)
        return ret

    """
    2. 目标节点的父节点是红色,目标节点是其父节点的右子节点;且叔叔节点是黑色
    """
    def is_need_left_rotate(self):
        ret = False
        parent = self.parent
        uncle = self.get_uncle()
        if(parent and parent.right == self and parent.is_red()):
            if(uncle and uncle.is_black()):
                ret = True
            elif not uncle:
                ret = True
        if(ret):
            print("need_left_rotate: ", self.value)

        return ret

    """
    3. 目标节点的父节点是红色,目标节点是其父节点的左子节点.且叔叔节点是黑色
    """
    def is_need_right_rotate(self):
        ret = False
        parent = self.parent
        uncle = self.get_uncle()
        if(parent and parent.is_red() and parent.left == self):
            if(uncle and uncle.is_black()):
                ret = True
            elif not uncle:
                ret = True

        if(ret):
            print("need_right_rotate: ", self.value)

        return ret

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
