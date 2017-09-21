import chardet

with open("../texts/gbk.txt", "rb") as file_handle:
    content = file_handle.read()
    print(chardet.detect(content))

with open("../texts/gb2312.txt", "rb") as file_handle:
    content = file_handle.read()
    print(chardet.detect(content))

with open("../texts/ucs2-be.txt", "rb") as file_handle:
    content = file_handle.read()
    print(chardet.detect(content))

with open("../texts/ucs2-le.txt", "rb") as file_handle:
    content = file_handle.read()
    print(chardet.detect(content))

with open("../texts/utf8-with-BOM.txt", "rb") as file_handle:
    content = file_handle.read()
    print(chardet.detect(content))
