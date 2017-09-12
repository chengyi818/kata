#!/usr/bin/env python3

# utf-8
a = b'\xe2\x82\xac'.decode("utf-8")
print(type(a))
print(a)

print(a.encode("gb18030"))
print(a.encode("gbk"))
