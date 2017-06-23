#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 16 Jun 2017 02:25:27 PM CST
# 滚动条
import tkinter as tk
root = tk.Tk()
root.title("hello world")
root.geometry()


def print_item(event):
    print(lb.get(lb.curselection()))


var = tk.StringVar()
lb = tk.Listbox(root, height=5, selectmode=tk.BROWSE,
                listvariable=var)
lb.bind('<ButtonRelease-1>', print_item)

list_item = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
for item in list_item:
    lb.insert(tk.END, item)

scrl = tk.Scrollbar(root)
scrl.pack(side=tk.RIGHT, fill=tk.Y)

lb.configure(yscrollcommand=scrl.set)
lb.pack(side=tk.LEFT, fill=tk.BOTH)
scrl['command'] = lb.yview

root.mainloop()
