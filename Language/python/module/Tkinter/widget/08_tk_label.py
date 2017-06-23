#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 07:08:11 PM CST
import tkinter

root = tkinter.Tk()
root.title("hello world")
root.geometry('300x200')

l1 = tkinter.Label(root, text="show", bg="green",
                   font=("Arial", 12), width=5, height=2)
l1.pack(side=tkinter.LEFT)  # 这里的side可以赋值为LEFT  RTGHT TOP  BOTTOM

l2 = tkinter.Label(root, text="show", bg="green",
                   font=("Arial", 12), width=5, height=2)
l2.pack(side=tkinter.LEFT)  # 这里的side可以赋值为LEFT  RTGHT TOP  BOTTOM

root.mainloop()
