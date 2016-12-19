#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import threading
import time

class TimeoutException(Exception):
    pass

def hello(name):
    print("hello %s\n" % name)
    raise TimeoutException

    # global TIMER
    # TIMER = threading.Timer(2.0, hello, ["Hawk"])
    # TIMER.start()

if __name__ == "__main__":
    TIMER = threading.Timer(2.0, hello, ["Hawk"])
    TIMER.start()
    try:
        while True:
            print("main running")
            time.sleep(1)
    except TimeoutException:
        print("catch TimeoutException")
