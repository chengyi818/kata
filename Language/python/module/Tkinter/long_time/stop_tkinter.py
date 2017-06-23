#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 21 Jun 2017 08:09:41 PM CST

from tkinter import Tk, Button
import random
import time

"""
after_cancel
"""


class example(object):
    def __init__(self, root):
        self._job = None
        self.root = root

    def cancel(self):
        if self._job is not None:
            self.root.after_cancel(self._job)
            self._job = None

    def goodbye_world(self):
        print("Stopping Feed")
        self.cancel()
        button.configure(text="Start Feed", command=self.hello_world)

    def hello_world(self):
        print("Starting Feed")
        button.configure(text="Stop Feed", command=self.goodbye_world)
        self.print_sleep()

    def print_sleep(self):
        foo = random.randint(4000, 7500)
        print("Sleeping: ", foo)
        self._job = self.root.after(1000, self.really_sleep)

    def really_sleep(self):
        num = 10
        while num:
            print(num)
            time.sleep(1)
            num -= 1
        self._job = self.root.after(1000, self.really_sleep)


root = Tk()
example_object = example(root)
button = Button(root, text="Start Feed", command=example_object.hello_world)

button.pack()


root.mainloop()
