#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import time
import signal

def test(j):
    time.sleep(j%4)
    print("%d within time"%(j))
    return j

if __name__ == '__main__':
    def handler(signum, frame):
        raise AssertionError

    i = 0
    for i in range(1, 10):
        try:
            signal.signal(signal.SIGALRM, handler)
            signal.alarm(3)
            test(i)
            i = i + 1
            signal.alarm(0)
        except AssertionError:
            print("%d timeout"%(i))
