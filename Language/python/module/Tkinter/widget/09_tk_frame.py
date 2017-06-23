#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 07:17:30 PM CST
# Frame布局
import tkinter

root = tkinter.Tk()
root.title("hello world")
root.geometry('300x200')

tkinter.Label(root, text='校训',
              font=('Arial', 20)).pack()

frm = tkinter.Frame(root)
frm.pack()

# left
frm_L = tkinter.Frame(frm)
frm_L.pack(side=tkinter.LEFT)

l1 = tkinter.Label(frm_L, text='厚德',
                   font=('Arial', 15))
l1.pack(side=tkinter.TOP)

l2 = tkinter.Label(frm_L, text='博学',
                   font=('Arial', 15))
l2.pack(side=tkinter.TOP)

# right
frm_R = tkinter.Frame(frm)
frm_R.pack(side=tkinter.RIGHT)

l3 = tkinter.Label(frm_R, text='敬业',
                   font=('Arial', 15))
l3.pack(side=tkinter.TOP)

l4 = tkinter.Label(frm_R, text='乐群',
                   font=('Arial', 15))
l4.pack(side=tkinter.TOP)


root.mainloop()
