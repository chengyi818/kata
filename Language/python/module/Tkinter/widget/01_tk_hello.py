#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 04:23:13 PM CST

# 1. 导入Tkinter模块
# 2. 创建控件
# 3. 指定这个控件的master, 即这个控件属于哪一个
# 4. 告诉GM(geometry manager)有一个控件产生了

# http://www.yiibai.com/python/python_gui_programming.html

import tkinter as tk

# 建立tkinter窗口，设置窗口标题
top = tk.Tk()
top.title("Hello Test")
top.geometry("600x400")
top.resizable(width=True, height=True)

# 在窗口中创建标签
labelHello = tk.Label(top, text="Hello Tkinter!", height=20, width=20)
labelHello.pack()

# 运行并显示窗口
top.mainloop()
