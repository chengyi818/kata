#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 04:41:27 PM CST
# 输入框
import tkinter as tk


def btnHelloClicked():
                cd = float(testCd.get())
                labelHello.config(text="%.2f°C = %.2f°F" % (cd, cd*1.8+32))


top = tk.Tk()

top.title("Entry Test")
labelHello = tk.Label(top, text="Convert °C to °F...",
                      height=5, width=20, fg="blue")
labelHello.pack()

# entryCd = tk.Entry(top, text="0", show="*", width=20)
# entryCd.pack()

var = tk.StringVar()
testCd = tk.Entry(top, textvariable=var)
var.set("0")
testCd.pack()

btnCal = tk.Button(top, text="Calculate", command=btnHelloClicked)
btnCal.pack()

top.mainloop()
