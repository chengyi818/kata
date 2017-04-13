#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

from collections import defaultdict

class BetterCountMissing(object):
    def __init__(self):
        self.added = 0

    def __call__(self):
        self.added += 1
        return 0

def main():
    current = {'green': 12, 'blue': 3}
    increments = [
        ('red', 5),
        ('blue', 17),
        ('orange', 9),
    ]

    counter = BetterCountMissing()
    result = defaultdict(counter, current)
    print('Before:', dict(result))

    for key, amount in increments:
        result[key] += amount
    print('After:', dict(result))
    print('Count Missing: ', counter.added)

if __name__ == '__main__':
    main()
