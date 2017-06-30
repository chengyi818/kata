#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 19 Jun 2017 06:35:55 PM CST
import datetime
import tkinter as tk

# widget name
# listbox_mid_left
# text_mid_right
# label_mario_version
# label_status
# label_current_loop_id
# label_log_stamp

widget_dict = {}


def add_widget(key, value):
    if key in widget_dict:
        print("dumplicate key")
        return
    else:
        widget_dict[key] = value


def get_widget(key):
    if key not in widget_dict:
        print("{0} not in widget_dict".format(key))
        return None
    else:
        return widget_dict[key]


def text_mid_right_insert(value):
    print("text_mid_right_insert:", value)
    text_mid_right = get_widget("text_mid_right")
    current_time = str(datetime.datetime.now()).split(".")[0]
    value = current_time + " " + value + "\n"

    text_mid_right.config(state=tk.NORMAL)
    text_mid_right.insert(tk.END, value)
    text_mid_right.config(state=tk.DISABLED)
