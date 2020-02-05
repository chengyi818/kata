#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 03 Feb 2020 04:58:01 PM CST

import sys
import clang.cindex
from clang.cindex import Config
from clang.cindex import Cursor
from clang.cindex import CursorKind

Config.set_library_file("/usr/lib/llvm-6.0/lib/libclang.so.1")


def find_typerefs(node, typename):
    """
    Find all references to the type named 'typename'
    """
    if node.kind.is_reference():
        ref_node = clang.cindex.cursor_ref(node)
        if ref_node.spelling == typename:
            print("Found %s [line=%s, col=%s]"%(typename, node.location.line, node.location.column))

    # Recurse for children of this node
    for c in node.get_children():
        find_typerefs(c, typename)

def showToken(node):
    ts = node.get_tokens()
    #print(node.type)
    #print(node.__dict__)
    for t in ts:
        print(t.kind.name + " : " + t.spelling)

def main():
    index = clang.cindex.Index.create()
    tu = index.parse(sys.argv[1])

    for i in tu.cursor.get_children():
        if(sys.argv[2] in i.displayname):
            print(i.displayname)
            showToken(i)

    #find_typerefs(tu.cursor, sys.argv[2])

if __name__ == "__main__":
    main()
