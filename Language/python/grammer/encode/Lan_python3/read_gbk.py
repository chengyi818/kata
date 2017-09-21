#!/usr/bin/env python3

content = '中'
file_path = "../texts/gbk.txt"
with open(file_path, "wb+") as file_handle:
    content_gbk = content.encode("gbk")
    file_handle.write(content_gbk)

with open(file_path, "r") as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
    print(content_read)

with open(file_path, "r", encoding='gbk') as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
    print(content_read)

with open(file_path, "r", encoding='utf-8') as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
    print(content_read)
