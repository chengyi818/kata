#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 08:57:53 PM CST
from rb_node import *
import rb_draw

class RbTree(object):
    def __init__(self):
        self.root = None


    def insert(self, value, color=RED):
        tmp_node = RbNode(value, color)

        # 插入节点为根节点
        if not self.root:
            self.root = tmp_node
            return

        # 找到目标插入点
        current = self.root
        while(current):
            if(current.value > tmp_node.value):
                if(current.left):
                    current = current.left
                else:
                    current.left = tmp_node
                    tmp_node.parent = current
                    return
            else:
                if(current.right):
                    current = current.right
                else:
                    current.right = tmp_node
                    tmp_node.parent = current
                    return

    def show(self):
        rb_draw.draw(self.root)

    # input: value
    # return: Node
    def search(self, value):
        current = self.root
        while(current and current.value != value):
            if(current.value > value):
                current = current.left
            else:
                current = current.left

        return current




