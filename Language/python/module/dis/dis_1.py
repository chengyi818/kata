#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 23 Oct 2017 07:47:49 PM CST
import dis


def main():
    with open("dis_1.py", "r") as file_handle:
        content = file_handle.read()
    co = compile(content, 'dis_1.py', 'exec')
    print(dir(co))
    dis_result = dis.dis(co)
    print(dis_result)


if __name__ == "__main__":
    main()
