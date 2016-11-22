#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import threading
import time

def hello(name):
    print "hello %s\n" % name

    global timer
    timer = threading.Timer(2.0, hello, ["Hawk"])
    timer.start()

if __name__ == "__main__":
    timer = threading.Timer(2.0, hello, ["Hawk"])
    timer.start()
