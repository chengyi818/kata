#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 16 Jun 2017 02:32:59 PM CST
import tkinter as tk
from tkinter.filedialog import askopenfilename


class MyFrame(tk.Frame):
    def __init__(self):
        tk.Frame.__init__(self)
        self.master.title("Example")
        self.master.rowconfigure(5, weight=1)
        self.master.columnconfigure(5, weight=1)
        self.grid(sticky=tk.W+tk.E+tk.N+tk.S)

        self.button = tk.Button(self, text="Browse",
                                command=self.load_file, width=10)
        self.button.grid(row=1, column=0, sticky=tk.W)

    def load_file(self):
        fname = askopenfilename(filetypes=(("Template files", "*.tplate"),
                                           ("HTML files", "*.html;*.htm"),
                                           ("All files", "*.*")))
        if fname:
            print(fname)


if __name__ == "__main__":
    MyFrame().mainloop()
