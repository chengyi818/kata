#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 13 May 2019 02:55:54 PM CST

from binascii import unhexlify
from Crypto.Cipher import AES
from Crypto.Protocol.SecretSharing import Shamir

shares = []
for x in range(2):
    in_str = input("Enter index and share separated by comma: ")
    idx, share = [s.strip() for s in in_str.split(",")]
    share = unhexlify(share)
    print(share, type(share), len((share)))
    shares.append((idx, share))
key = Shamir.combine(shares)
