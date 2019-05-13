#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 13 May 2019 01:53:36 PM CST
# https://pycryptodome.readthedocs.io/en/latest/src/cipher/classic.html#ctr-mode

import json
from base64 import b64decode, b64encode

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

key = get_random_bytes(16)


def encryption(data, key):
    cipher = AES.new(key, AES.MODE_CTR)
    ct_bytes = cipher.encrypt(data)
    nonce = b64encode(cipher.nonce).decode('utf-8')
    ct = b64encode(ct_bytes).decode('utf-8')
    result = json.dumps({'nonce': nonce, 'ciphertext': ct})
    return result


# We assume that the key was securely shared beforehand
def decryption(json_input, key):
    try:
        b64 = json.loads(json_input)
        nonce = b64decode(b64['nonce'])
        ct = b64decode(b64['ciphertext'])
        cipher = AES.new(key, AES.MODE_CTR, nonce=nonce)
        pt = cipher.decrypt(ct)
        return pt
    except Exception as e:
        print("Incorrect decryption: ", e)


if __name__ == "__main__":
    data = b"secret"
    encrypted = encryption(data, key)
    print("encrypted: ", encrypted)

    decrypted = decryption(encrypted, key)
    print("decrypted: ", decrypted)
