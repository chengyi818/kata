#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 13 May 2019 02:55:26 PM CST

from binascii import hexlify
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Protocol.SecretSharing import Shamir

# split
shares2 = []
key = get_random_bytes(16)
shares = Shamir.split(2, 5, key)
for idx, share in shares:
    print(idx, type(share), hexlify(share))
    if (idx == 2 or idx == 5):
        shares2.append((idx, share))

# encrypt
with open("clear_file.txt", "rb") as fi:
    with open("enc_file.txt", "wb") as fo:
        cipher = AES.new(key, AES.MODE_GCM)
        ct, tag = cipher.encrypt(fi.read()), cipher.digest()
        fo.write(cipher.nonce + tag + ct)

# decrypt
key = Shamir.combine(shares2)
fi = open("enc_file.txt", "rb")
nonce, tag = [fi.read(16) for x in range(2)]
cipher = AES.new(key, AES.MODE_GCM, nonce)
try:
    result = cipher.decrypt(fi.read())
    cipher.verify(tag)
    with open("clear_file2.txt", "wb") as fo:
        fo.write(result)
except ValueError:
    print("The shares were incorrect")
