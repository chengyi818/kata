#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import signal
import time
# Define signal handler function
def myHandler(signum, frame):
    print("Now, it's the time")
    exit()

# register signal.SIGALRM's handler
signal.signal(signal.SIGALRM, myHandler)
signal.alarm(5)
while True:
    time.sleep(1)
    print('not yet')
