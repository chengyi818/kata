#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 04:04:00 PM CST

import tkinter as tk


def print_item(event):
    print(lb.get(lb.curselection()))


root = tk.Tk()                     # 创建窗口对象的背景色
root.title("hello world")
root.geometry("600x400")


var = tk.StringVar()
lb = tk.Listbox(root, listvariable=var)
lb.pack()

list_item = [1, 2, 3, 4]         # 控件的内容为1 2 3 4
for item in list_item:
    lb.insert(tk.END, item)

lb.delete(2, 4)                  # 此时控件的内容为1 3

var.set(('a', 'ab', 'c', 'd'))   # 重新设置了，这时控件的内容就编程var的内容了
print(var.get())
lb.bind('<ButtonRelease-3>', print_item)  # 1是左键,3是右键

root.mainloop()                 # 进入消息循环
