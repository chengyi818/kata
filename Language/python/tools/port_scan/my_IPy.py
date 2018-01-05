#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 18 Dec 2017 06:16:01 PM CST

from IPy import IP

ip = IP("192.168.1.0").make_net("255.255.255.0")
# ip = IP(tmp)
print(ip.len)
for x in ip:
    print(x)
