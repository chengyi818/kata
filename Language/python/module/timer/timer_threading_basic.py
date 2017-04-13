#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import threading
import time

class Test(threading.Thread):
    def __init__(self, name, delay):
        threading.Thread.__init__(self)
        self.name = name
        self.delay = delay

    def run(self):
        print(self.name, " delay for ", self.delay)
        time.sleep(self.delay)
        count = 0
        while True:
            print("This is thread ", self.name, " on line ", count)
            count += 1
            if count == 3:
                print("End thread ", self.name)
                break


def main():
    thread_1 = Test('Thread 1', 2)
    thread_2 = Test('Thread 2', 2)
    thread_1.start()
    print("Wait thread_1 to end")
    thread_1.join()
    thread_2.start()
    print("End main")


if __name__ == "__main__":
    main()
