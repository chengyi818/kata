#!/usr/bin/env python3

# "中" gbk
a = b"\xd6\xd0"

print(type(a))
print(a)

print(a.decode('gbk'))
print(a.decode('utf-8'))
