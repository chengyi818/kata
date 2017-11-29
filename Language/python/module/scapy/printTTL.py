#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 27 Nov 2017 04:59:59 PM CST


from scapy.all import IP, conf, sniff


def testTTL(pkt):
    try:
        if pkt.haslayer(IP):
            ipsrc = pkt.getlayer(IP).src
            ttl = pkt.ttl
            print("Pkt Received from: ", ipsrc, "with TTL: ", ttl)
    except:
        pass


def main():
    sniff(prn=testTTL, store=0)


if __name__ == "__main__":
    print(conf.iface)
    main()
