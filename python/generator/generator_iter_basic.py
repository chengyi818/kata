#!/usr/bin/env python3
'''
# =============================================================================
#      FileName: test.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-06 10:24:32
#       Version: 0.0.1
#    LastChange: 2016-12-08 19:00:08
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

def normalize(numbers):
    total = sum(numbers)
    result = []
    for value in numbers:
        percent = 100 * value/total
        result.append(percent)
    return result

def read_visits(data_path):
    with open(data_path) as f:
        for line in f:
            yield int(line)

it = read_visits('my_numbers')
percentages = normalize(it)

print(percentages)

