#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 09:15:04 PM CST
import rb_tree
from rb_node import *

def main():
    print("main")
    t = rb_tree.RbTree()
    t.insert(1, BLACK)
    t.insert(3, RED)
    t.insert(7, BLACK)
    t.insert(8, RED)
    t.insert(2, BLACK)
    t.insert(4, BLACK)
    t.insert(5, BLACK)
    t.insert(6, BLACK)
    t.insert(9, BLACK)
    t.show()

if __name__ == "__main__":
    main()
