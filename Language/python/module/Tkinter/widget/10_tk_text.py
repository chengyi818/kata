#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 07:44:35 PM CST
# 文本输入

import tkinter as tk


def btnClearClicked():
    t.delete(1.0, tk.END)


def btnShowClicked():
    t.insert(1.0, 'hello\n')
    t.insert(tk.END, 'hello000000\n')
    t.insert(tk.END, 'nono')


root = tk.Tk()
root.title("hello world")
root.geometry('600x600')

t = tk.Text(root)
t.pack()

btn1 = tk.Button(root, text="Show", command=btnShowClicked)
btn1.pack()

btn2 = tk.Button(root, text="Clear", command=btnClearClicked)
btn2.pack()


root.mainloop()
