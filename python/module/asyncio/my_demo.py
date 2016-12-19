#!/usr/bin/env python3
# -*- coding: UTF-8 -*-


import asyncio
import time

@asyncio.coroutine
def my_timer(timeout_second):
    print("timer start")
    yield from asyncio.sleep(timeout_second)
    print("timer alarm")
    raise AssertionError

@asyncio.coroutine
def normal_task():
    while True:
        print("normal task working")
        time.sleep(1)

def main():
    timeout_second = 5

    loop = asyncio.get_event_loop()
    tasks = [my_timer(timeout_second), normal_task()]
    try:
        loop.run_until_complete((tasks))
    except AssertionError:
        print("normal_task timeout")
    finally:
        loop.close()

if __name__ == '__main__':
    main()
