#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 16 Jun 2017 04:20:06 PM CST
import tkinter as tk
from sf_gui.sf_buttoner import SfButton
from sf_base import sf_const
from sf_gui import sf_register


class SfFrame(object):
    def __init__(self, root):
        print("SfFrame init")
        self.root = root

    def run(self):
        print("SfFrame run")
        self.__prepare_frame()

    def __prepare_frame(self):
        # root frame
        frm_root = tk.Frame(self.root)
        frm_root.pack()

        self.__prepare_frm_top(self.root, frm_root)
        self.__prepare_frm_mid(frm_root)
        self.__prepare_frm_bottom(frm_root)

    def __prepare_frm_top(self, root, frm_root):
        # top frame
        frm_top = tk.Frame(frm_root)
        frm_top.pack(side=tk.TOP)
        self.__prepare_buttons(root, frm_top)

    def __prepare_frm_mid(self, frm_root):
        # mid frame
        frm_mid = tk.Frame(frm_root)
        frm_mid.pack()

        frm_mid_left = tk.Frame(frm_mid)
        frm_mid_left.pack(side=tk.LEFT)
        self.__prepare_mid_left_listbox(frm_mid_left)

        frm_mid_right = tk.Frame(frm_mid)
        frm_mid_right.pack(side=tk.RIGHT)
        self.__prepare_mid_right_text(frm_mid_right)

    def __prepare_frm_bottom(self, frm_root):
        # bottom frame
        frm_bottom = tk.Frame(frm_root)
        frm_bottom.pack(side=tk.BOTTOM)
        self.__prepare_bottom_label(frm_bottom)

    def __prepare_mid_left_listbox(self, frm_mid_left):
        scrl = tk.Scrollbar(frm_mid_left)
        scrl.pack(side=tk.RIGHT, fill=tk.Y)

        listbox_mid_left = tk.Listbox(frm_mid_left,
                                      width=sf_const.MID_LEFT_LISTBOX_WIDTH,
                                      height=sf_const.MID_LEFT_LISTBOX_HEIGHT)

        listbox_mid_left.pack(side=tk.LEFT)
        listbox_mid_left.configure(yscrollcommand=scrl.set)

        scrl['command'] = listbox_mid_left.yview

        sf_register.add_widget("listbox_mid_left", listbox_mid_left)

    def __prepare_mid_right_text(self, frm_mid_right):
        scrl = tk.Scrollbar(frm_mid_right)
        scrl.pack(side=tk.RIGHT, fill=tk.Y)

        text_mid_right = tk.Text(frm_mid_right,
                                 width=sf_const.MID_RIGHT_TEXT_WIDTH,
                                 height=sf_const.MID_RIGHT_TEXT_HEIGHT)

        text_mid_right.config(state=tk.DISABLED)
        text_mid_right.pack(side=tk.LEFT, fill=tk.BOTH)

        text_mid_right.configure(yscrollcommand=scrl.set)

        scrl['command'] = text_mid_right.yview

        sf_register.add_widget("text_mid_right", text_mid_right)

    def __prepare_buttons(self, root, frm_top):
        buttoner = SfButton(root, frm_top)
        buttoner.run()

    def __prepare_bottom_label(self, frm_bottom):
        label_mario_version = tk.Label(frm_bottom, text="Mario版本:\n TODO",
                                       width=sf_const.BOTTOM_LABEL_WIDTH,
                                       height=sf_const.BOTTOM_LABEL_HEIGHT)
        label_mario_version.pack(side=tk.LEFT)
        sf_register.add_widget("label_mario_version", label_mario_version)

        label_status = tk.Label(frm_bottom, text="当前状态:\n TODO",
                                width=sf_const.BOTTOM_LABEL_WIDTH,
                                height=sf_const.BOTTOM_LABEL_HEIGHT)
        label_status.pack(side=tk.LEFT)
        sf_register.add_widget("label_status", label_status)

        label_current_loop_id = tk.Label(frm_bottom, text="当前第XX轮测试",
                                         width=sf_const.BOTTOM_LABEL_WIDTH,
                                         height=sf_const.BOTTOM_LABEL_HEIGHT)

        label_current_loop_id.pack(side=tk.LEFT)
        sf_register.add_widget("label_current_loop_id", label_current_loop_id)

        label_log_stamp = tk.Label(frm_bottom, text="离上次清理log: XX小时",
                                   width=sf_const.BOTTOM_LABEL_WIDTH,
                                   height=sf_const.BOTTOM_LABEL_HEIGHT)

        label_log_stamp.pack(side=tk.LEFT)
        sf_register.add_widget("label_log_stamp", label_log_stamp)
