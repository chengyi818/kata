#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 13 May 2019 10:09:36 AM CST

import hmac

SECRET_KEY = b'pseudorandomly generated server secret key'


def sign(cookie):
    h = hmac.new(key=SECRET_KEY, digestmod='sha256')
    h.update(cookie)
    return h.hexdigest().encode('utf-8')


def verify(cookie, sig):
    good_sig = sign(cookie)
    return hmac.compare_digest(good_sig, sig)


cookie = b'user-alice'
sig = sign(cookie)
print("{0},{1}".format(cookie.decode('utf-8'), sig))

print(verify(cookie, sig))
print(verify(b'user-bob', sig))
print(verify(cookie, b'0102030405060708090a0b0c0d0e0f00'))
