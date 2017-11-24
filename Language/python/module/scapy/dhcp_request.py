#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 23 Nov 2017 11:00:28 AM CST

from scapy.all import *

conf.checkIPaddr = False
fam, hw = get_if_raw_hwaddr(conf.iface)

dhcp_discover = Ether(dst="ff:ff:ff:ff:ff:ff")/IP(src="0.0.0.0", dst="255.255.255.255")/UDP(sport=68,dport=67)/BOOTP(chaddr=hw)/DHCP(options=[("message-type","discover"), "end"])

ans, unans = srploop(dhcp_discover, multi=True)
ans.summary()

for p in ans:
    print(p[1][Ether].src, p[1][IP].src)
