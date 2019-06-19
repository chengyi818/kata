#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 19 Jun 2019 11:15:46 AM CST

a = [1, 1, 2, 2]
b = [1, 2]
c = []

for i in a:
    # print(i)
    if i not in b:
        c.append(i)
        # a.remove(i)

print(a)
print(c)
