#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 16 Jun 2017 03:51:11 PM CST
import os
import tkinter as tk
from sf_base import sf_const
from sf_gui import sf_framer
from sf_utils import sf_os


class SfLayout(object):
    def __init__(self):
        print("SfLayout init")
        self.root = None

    def run(self):
        print("SfLayout run")
        self.__prepare_root()
        self.__prepare_frame()
        self.__prepare_over()

    def __prepare_root(self):
        self.root = tk.Tk()
        self.root.title(sf_const.WINDOW_NAME)
        self.root.geometry(sf_const.WINDOW_SIZE)

        icon_location = os.path.join(sf_os.get_pwd(),
                                     "sf_base",
                                     sf_const.ICON)
        img = tk.PhotoImage(file=icon_location)
        self.root.tk.call("wm", 'iconphoto', self.root._w, img)

    def __prepare_frame(self):
        framer = sf_framer.SfFrame(self.root)
        framer.run()

    def __prepare_over(self):
        self.root.mainloop()
