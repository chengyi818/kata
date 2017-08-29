#!/usr/bin/env python3
import codecs

content = '中'
with open("text_gbk.txt", "wb+") as file_handle:
    content_gbk = content.encode("gbk")
    file_handle.write(content_gbk)

with open("text_gbk.txt", "r") as file_handle:
    print("hello world")
    # content_read = file_handle.read()
    # print(content_read)

with codecs.open("text_gbk.txt", "r", 'gbk') as file_handle:
    content_read = file_handle.read()
    print(content_read)
