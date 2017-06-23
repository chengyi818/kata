#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 05:23:43 PM CST
# -*- coding:cp936 -*-
import tkinter as tk


class show(object):
    num_info_hash = {}
    char_info_hash = {}
    num_char = {}
    char_num = {}

    def __init__(self):
        self.root = tk.Tk()
        self.root.title("ASCII码查询")
        self.root.geometry('470x320')
        ########
        self.frm = tk.Frame(self.root)
        # Top
        tk.Label(self.root, text="ASCII码查询", font=('Arial', 15)).pack()
        self.load_sys()
        self.frm = tk.Frame(self.root)
        # Left
        self.frm_L = tk.Frame(self.frm)
        self.frm_LT = tk.Frame(self.frm_L)
        self.var_char = tk.StringVar()
        tk.Entry(self.frm_LT, textvariable=self.var_char,
                 width=5, font=('Verdana', 15)).pack(side=tk.RIGHT)
        tk.Label(self.frm_LT, text='字符',
                 font=('Arial', 12)).pack(side=tk.LEFT)
        self.frm_LT.pack()

        self.var_L_char = tk.StringVar()
        self.lb_char = tk.Listbox(self.frm_L, selectmode=tk.BROWSE,
                                  listvariable=self.var_L_char,
                                  font=('Verdana', 12),
                                  width=10, height=13)
        self.lb_char.bind('<ButtonRelease-1>', self.get_char)
        for key in self.char_num:
            self.lb_char.insert(tk.END, key[0])
        self.scrl_char = tk.Scrollbar(self.frm_L)
        self.scrl_char.pack(side=tk.RIGHT, fill=tk.Y)
        self.lb_char.configure(yscrollcommand=self.scrl_char.set)
        self.lb_char.pack(side=tk.LEFT, fill=tk.BOTH)
        self.scrl_char['command'] = self.lb_char.yview

        self.frm_L.pack(side=tk.LEFT)

        # Mid
        self.frm_M = tk.Frame(self.frm)
        self.t_show = tk.Text(self.frm_M, width=20, height=5,
                              font=('Verdana', 15))
        self.t_show.insert('1.0', '')
        self.t_show.pack()

        self.frm_MB = tk.Frame(self.frm_M)
        tk.Button(self.frm_MB, text="清除", command=self.clear, width=6,
                  height=1, font=('Arial', 10)).pack(side=tk.LEFT)
        tk.Button(self.frm_MB, text="查询", command=self.search, width=6,
                  height=1, font=('Arial', 10)).pack(side=tk.RIGHT)
        self.frm_MB.pack(side=tk.BOTTOM)

        self.frm_M.pack(side=tk.LEFT)

        # Right
        self.frm_R = tk.Frame(self.frm)
        self.frm_RT = tk.Frame(self.frm_R)
        self.var_int = tk.StringVar()
        tk.Entry(self.frm_RT, textvariable=self.var_int, width=5,
                 font=('Verdana', 15)).pack(side=tk.LEFT)
        tk.Label(self.frm_RT, text='十进制',
                 font=('Arial', 12)).pack(side=tk.RIGHT)
        self.frm_RT.pack()
        self.var_R_int = tk.StringVar()
        self.lb_int = tk.Listbox(self.frm_R, selectmode=tk.BROWSE,
                                 listvariable=self.var_R_int,
                                 font=('Verdana', 12), width=10, height=13)
        self.lb_int.bind('<ButtonRelease-1>', self.get_int,)
        for key in self.num_char:
            self.lb_int.insert(tk.END, key[0])
        self.scrl_int = tk.Scrollbar(self.frm_R)
        self.scrl_int.pack(side=tk.RIGHT, fill=tk.Y)
        self.lb_int.configure(yscrollcommand=self.scrl_int.set)
        self.lb_int.pack(side=tk.LEFT, fill=tk.BOTH)
        self.scrl_int['command'] = self.lb_int.yview

        self.frm_R.pack(side=tk.LEFT)

        self.frm.pack()
        ########

    def get_char(self, event):
        self.var_char.set('')
        self.var_int.set('')
        tmp = self.lb_char.get(self.lb_char.curselection())
        self.var_char.set(tmp)

    def get_int(self, event):
        self.var_int.set('')
        self.var_char.set('')
        tmp = self.lb_int.get(self.lb_int.curselection())
        self.var_int.set(tmp)

    def clear(self):
        self.var_char.set('')
        self.var_int.set('')
        self.t_show.delete('1.0', '10.0')

    def search(self):
        self.t_show.delete('1.0', '100.0')
        tmp_char = self.var_char.get()
        tmp_int = self.var_int.get()
        if tmp_char != '':
            if tmp_char not in self.char_info_hash:
                self.t_show.insert('1.0', "您输入的字符不在128个字符之内")
            else:
                self.t_show.insert('1.0', '十六进制:' + '\t' +
                                   self.char_info_hash[tmp_char][2] + '\n')
                self.t_show.insert('1.0', '十进制:' + '\t' +
                                   self.char_info_hash[tmp_char][1] + '\n')
                self.t_show.insert('1.0', '八进制:' + '\t' +
                                   self.char_info_hash[tmp_char][0] + '\n')
                self.t_show.insert('1.0', '字符:' + '\t' +
                                   tmp_char + '\n\n')
            self.var_char.set('')
            self.var_int.set('')
        elif tmp_int != '':
            if tmp_int not in self.num_info_hash:
                self.t_show.insert('1.0', "请输入介于0~127之间的整数")
            else:
                self.t_show.insert('1.0', '字符:' + '\t' +
                                   self.num_info_hash[tmp_int][2] + '\n')
                self.t_show.insert('1.0', '十六进制:' + '\t' +
                                   self.num_info_hash[tmp_int][1] + '\n')
                self.t_show.insert('1.0', '八进制:' + '\t' +
                                   self.num_info_hash[tmp_int][0] + '\n')
                self.t_show.insert('1.0', '十进制:' + '\t' +
                                   tmp_int + '\n\n')
            self.var_char.set('')
            self.var_int.set('')
        else:
            self.t_show.insert('1.0', '请选择或输入')

    def load_sys(self):
        with open("asc", "r") as f:
            for line in f:
                chunk = line.strip().split()
                self.num_char[int(chunk[1])] = chunk[3]
                self.char_num[chunk[3]] = int(chunk[1])
                self.num_info_hash[chunk[1]] = [chunk[0], chunk[2], chunk[3]]
                self.char_info_hash[chunk[3]] = [chunk[0], chunk[1], chunk[2]]

            self.num_char = sorted(self.num_char.iteritems(),
                                   key=lambda asd: asd[0])
            self.char_num = sorted(self.char_num.iteritems(),
                                   key=lambda asd: asd[1])


def main():
    d = show()
    d.root.mainloop()


if __name__ == "__main__":
    main()
