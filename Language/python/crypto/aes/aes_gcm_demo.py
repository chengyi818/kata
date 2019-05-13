#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 13 May 2019 02:00:23 PM CST

import json
from base64 import b64decode, b64encode

from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

key = get_random_bytes(16)


def encryption(data, key):
    cipher = AES.new(key, AES.MODE_GCM)
    ciphertext, tag = cipher.encrypt_and_digest(data)
    json_k = ['nonce', 'ciphertext', 'tag']
    json_v = [
        b64encode(x).decode('utf-8') for x in (cipher.nonce, ciphertext, tag)
    ]
    result = json.dumps(dict(zip(json_k, json_v)))

    return result


# We assume that the key was securely shared beforehand
def decryption(json_input, key):
    try:
        b64 = json.loads(json_input)
        json_k = ['nonce', 'ciphertext', 'tag']
        jv = {k: b64decode(b64[k]) for k in json_k}

        cipher = AES.new(key, AES.MODE_GCM, nonce=jv['nonce'])
        plaintext = cipher.decrypt_and_verify(jv['ciphertext'], jv['tag'])
        return plaintext
    except Exception as e:
        print("Incorrect decryption: ", e)


if __name__ == "__main__":
    data = b"secret"
    encrypted = encryption(data, key)
    print("encrypted: ", encrypted)

    decrypted = decryption(encrypted, key)
    print("decrypted: ", decrypted)
