#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: main.py
#          Desc: main-->module_x
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-26 15:14:00
#       Version: 0.0.1
#    LastChange: 2016-11-26 15:14:01
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''
from subpackage1 import module_x
from subpackage1.module_x import ModuleX

def main():
    module_x.func_x()
    my_x = ModuleX()
    my_x.my_print()


if __name__ == "__main__":
    main()
