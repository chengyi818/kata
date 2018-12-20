#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Dec 2018 09:15:04 PM CST
from cmd import Cmd
import sys
import rb_tree
import rb_node


def test():
    print("main")
    t = rb_tree.RbTree()
    t.insert(1, rb_node.BLACK)
    t.insert(3, rb_node.RED)
    t.insert(2, rb_node.BLACK)
    t.show()


class RbTreeConsole(Cmd):
    def __init__(self):
        Cmd.__init__(self)
        self.tree = rb_tree.RbTree()

    def help_i(self):
        print("insert value [color]")

    def do_i(self, value):
        self.tree.insert(int(value))
        self.tree.show()

    def help_exit(self):
        print("exit")

    def do_exit(self, s):
        print("ByeBye: ", s)
        sys.exit()

    do_EOF = do_exit
    help_EOF = help_exit


if __name__ == "__main__":
    cmd = RbTreeConsole()
    cmd.cmdloop()
