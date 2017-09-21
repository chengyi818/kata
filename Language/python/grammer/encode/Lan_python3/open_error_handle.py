#!/usr/bin/env python3

content = '中'
file_path = "../texts/gbk.txt"
with open(file_path, "wb+") as file_handle:
    content_gbk = content.encode("gbk")
    file_handle.write(content_gbk)


# error handle: surrogateescape
with open(file_path, "r+", encoding='utf-8',
          errors="surrogateescape") as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
    print(repr(content_read))
    # file_handle.writelines(content_read)

# error handle: backslashreplace
with open(file_path, "r", encoding='utf-8',
          errors="backslashreplace") as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
    print(repr(content_read))

# error handle: replace
with open(file_path, "r", encoding='utf-8',
          errors="replace") as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
    print(repr(content_read))

# error handle: ignore
with open(file_path, "r", encoding='utf-8',
          errors="ignore") as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
    print(repr(content_read))

# no error handle, default: strict
with open(file_path, "r") as file_handle:
    content_read = file_handle.read()
    print(type(content_read))
