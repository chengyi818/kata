#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import multiprocessing
import queue
import time

TIMEOUT = 5

def big_loop(bob):
    time.sleep(4)
    return bob*2

def wrapper(my_queue, bob):
    result = big_loop(bob)
    my_queue.put(result)
    my_queue.close()

def run_loop_with_timeout():
    bob = 21 # Whatever sensible value you need
    my_queue = multiprocessing.Queue(1) # Maximum size is 1
    proc = multiprocessing.Process(target=wrapper, args=(my_queue, bob))
    proc.start()

    # Wait for TIMEOUT seconds
    try:
        result = my_queue.get(True, TIMEOUT)
    except queue.Empty:
    # Deal with lack of data somehow
        result = None
    finally:
        proc.terminate()

    # Process data here, not in try block above, otherwise your process keeps running
        print(result)

if __name__ == "__main__":
    run_loop_with_timeout()
