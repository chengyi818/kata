#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 16 Jun 2017 03:32:22 PM CST
from sf_gui.sf_layouter import SfLayout


class SfTask(object):
    def __init__(self):
        print("SfTask init")
        self.layouter = SfLayout()

    def run(self):
        print("SfTask run")
        # prepare layout
        self.layouter.run()
