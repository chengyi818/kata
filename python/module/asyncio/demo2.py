#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import threading
import asyncio

@asyncio.coroutine
def hello():
    print('Hello world! (%s)' % threading.currentThread())
    yield from asyncio.sleep(1)
    print('Hello again! (%s)' % threading.currentThread())

loop = asyncio.get_event_loop()
tasks = [hello(), hello()]
print("main thread: ", threading.currentThread())
loop.run_until_complete(asyncio.wait(tasks))
loop.close()
