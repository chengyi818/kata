#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 08 May 2019 05:37:27 PM CST

import base64

from Crypto.Cipher import AES

# Java
# Cipher.getInstance("AES/ECB/PKCS5Padding")
# 明文长度必须是密钥长度的倍数
# 不安全


def pad(s):
    BS = 16
    return s + (BS - len(s) % BS) * chr(BS - len(s) % BS)


def unpad(s):
    return s[0:-s[-1]]


class AEScoder():
    def __init__(self):
        self.__encryptKey = "iEpSxImA0vpMUAabsjJWug=="
        self.__key = base64.b64decode(self.__encryptKey)

    # AES加密
    def encrypt(self, data):
        cipher = AES.new(self.__key, AES.MODE_ECB)
        encrData = cipher.encrypt(pad(data))
        return encrData

    # AES解密
    def decrypt(self, encrData):
        cipher = AES.new(self.__key, AES.MODE_ECB)
        decrData = unpad(cipher.decrypt(encrData))
        return decrData.decode('utf-8')


if __name__ == '__main__':
    # 初始化密钥
    pc = AEScoder()
    e = pc.encrypt("0123456789ABCD")
    d = pc.decrypt(e)
    print(e, d)

    e = pc.encrypt("00000000000000000000000000")
    d = pc.decrypt(e)
    print(e, d)
