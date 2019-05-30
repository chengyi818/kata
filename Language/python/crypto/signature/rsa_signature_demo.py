#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 13 May 2019 02:45:11 PM CST

from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15

# sign
message = 'To be signed'.encode('utf-8')
key = RSA.import_key(open('private.pem').read())
h = SHA256.new(message)
signature = pkcs1_15.new(key).sign(h)
print("signature: ", signature)

# verify
key = RSA.import_key(open('receiver.pem').read())
h = SHA256.new(message)
try:
    pkcs1_15.new(key).verify(h, signature)
    print("The signature is valid.")
except (ValueError, TypeError):
    print("The signature is not valid.")
