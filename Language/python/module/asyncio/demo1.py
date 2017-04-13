#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import asyncio

@asyncio.coroutine
def hello():
    print("hello world")
    r = yield from asyncio.sleep(3)
    print("hello again")

loop = asyncio.get_event_loop()
loop.run_until_complete(hello())
loop.close

