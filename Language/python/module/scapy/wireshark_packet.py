from scapy.all import *

packets = Ether()/IP(dst=Net("www.baidu.com/30"))/ICMP()
wireshark(packets)
