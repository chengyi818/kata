#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import threading
import time

import _thread

class TimeoutException(Exception):
    pass

def hello(name):
    print("hello %s\n" % name)
    # raise TimeoutException
    _thread.interrupt_main()

    # global TIMER
    # TIMER = threading.Timer(2.0, hello, ["Hawk"])
    # TIMER.start()

if __name__ == "__main__":
    TIMER = threading.Timer(5.0, hello, ["Hawk"])
    TIMER.start()
    try:
        while True:
            print("main running")
            time.sleep(1)
    except TimeoutException:
        print("catch TimeoutException")
