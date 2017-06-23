#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 04:30:07 PM CST
# 按钮

import tkinter as tk


def btnHelloClicked():
    labelHello.config(text="Hello Tkinter!")


top = tk.Tk()
top.title("Button Test")

labelHello = tk.Label(top, text="Press the button...",
                      height=5, width=20, fg="blue")
labelHello.pack()

btn = tk.Button(top, text="Hello", command=btnHelloClicked)
btn.pack()

top.mainloop()
