#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 08:57:53 PM CST
import rb_node
import rb_draw
from multiprocessing import Process


class RbTree(object):
    def __init__(self):
        self.root = None
        self.index = 0

    def insert(self, value, color=rb_node.RED):
        tmp_node = rb_node.RbNode(value, color)

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
        self.index += 1
        p = Process(target=self._show, args=(self.root, self.index))
        p.start()

    def _show(self, root, index):
        rb_draw.draw(root, index)

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




