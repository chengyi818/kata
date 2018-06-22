#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 22 Jun 2018 11:02:24 AM CST

class T(object):
    name = 'name'

    def hello(self):
        print("hello")

t = T()

class Descriptor(object):
    def __get__(self, obj, type=None):
            return 'get', self, obj, type

    def __set__(self, obj, val):
        print ('set', self, obj, val)

    def __delete__(self, obj):
        print('delete', self, obj)

print("-------------------------------------------------")
print('dir(t): ', dir(t))
print('dir(T): ', dir(T))
print('t.__dict__: ', t.__dict__)
print('T.__dict__: ', T.__dict__)
print("-------------------------------------------------")
print("T.__dict__['hello']: ", T.__dict__['hello'])
print('T.hello: ', T.hello)
print('t.hello: ', t.hello)
