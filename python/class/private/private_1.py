#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

class MyParentObject(object):
    def __init__(self):
        self.__private_field = 71

class MyChildObject(MyParentObject):
    def get_private_field(self):
        return self.__private_field


BAZ = MyChildObject()

#able to access father's private data
print(BAZ._MyParentObject__private_field)
# print(BAZ.get_private_field())
# print(BAZ.__dict__['_MyParentObject__private_field'])
