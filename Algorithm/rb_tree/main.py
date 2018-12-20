#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 09:15:04 PM CST
from cmd import Cmd
import sys
import rb_tree
import rb_node


def test():
    # test_change_color()
    # test_left_rotate()
    test_right_rotate()

def test_change_color():
    t = rb_tree.RbTree()
    t.insert(50, rb_node.BLACK)
    t.insert(27, rb_node.RED)
    t.insert(72, rb_node.RED)
    t.insert(100)
    t.show()
    t.change_color(t.search(100))
    t.show()


def test_left_rotate():
    t = rb_tree.RbTree()
    t.insert(80)
    t.insert(120)
    t.insert(40, rb_node.BLACK)
    t.insert(60)
    t.insert(20)
    t.insert(70)
    t.insert(50)

    t.show()
    t.left_rotate(t.search(40))
    t.show()


def test_right_rotate():
    t = rb_tree.RbTree()
    t.insert(80)
    t.insert(40)
    t.insert(120, rb_node.BLACK)
    t.insert(140)
    t.insert(100)
    t.insert(110)
    t.insert(90)


    t.show()
    t.right_rotate(t.search(120))
    t.show()


class RbTreeConsole(Cmd):
    def __init__(self):
        Cmd.__init__(self)
        self.tree = rb_tree.RbTree()

    def help_i(self):
        print("insert value [color]")

    def do_i(self, value):
        input_list = value.split()
        for tmp in input_list:
            self.tree.insert(int(tmp))

    def help_s(self):
        print("show tree")

    def do_s(self, value):
        self.tree.show()

    def help_exit(self):
        print("exit")

    def do_exit(self, s):
        print("ByeBye!")
        sys.exit()

    do_EOF = do_exit
    help_EOF = help_exit


if __name__ == "__main__":
    # test()
    cmd = RbTreeConsole()
    cmd.cmdloop()
