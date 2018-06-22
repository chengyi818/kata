#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 22 Jun 2018 11:26:46 AM CST
class Data_Descriptor(list):
    def __get__(self, obj, type=None):
        print('get', self, obj, type)
        return self

    def __set__(self, obj, val):
        print ('set', self, obj, val)
        self.append(val)

class Non_Data_Descriptor(list):
    def __get__(self, obj, type=None):
        print('get', self, obj, type)
        return self

class A(object):
    data_descriptor = Data_Descriptor()
    non_data_descriptor = Non_Data_Descriptor()

    def hello(self):
        print("hello")


a = A()
print("-------------------------------------------------")
a.data_descriptor
a.data_descriptor = 3
a.data_descriptor

print("-------------------------------------------------")
a.non_data_descriptor
a.non_data_descriptor = 3
print(a.non_data_descriptor)

print("-------------------------------------------------")
A.data_descriptor
A.data_descriptor = 3
print(A.data_descriptor)

print("-------------------------------------------------")
print(a.hello)
print(A.hello)
a.hello = 'world'
print(a.hello)
print(A.hello)
