#!/usr/bin/env python2
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 28 Nov 2017 02:19:06 PM CST


class TypeSetter(object):
    def __init__(self, fieldtype):
        print("TypeSetter __init__", fieldtype)
        self.fieldtype = fieldtype

    def is_valid(self, value):
        return isinstance(value, self.fieldtype)


class TypeCheckMeta(type):
    def __new__(cls, name, bases, dict):
        print("TypeCheckMeta __new__")
        print("name: ", name)
        print("bases: ", bases)
        print("dict: ", dict)
        return super(TypeCheckMeta, cls).__new__(cls, name, bases, dict)

    def __init__(cls, name, bases, dict):
        print("TypeCheckMeta __init__")
        cls._fields = {}
        for key, value in dict.items():
            if isinstance(value, TypeSetter):
                print("key: ", key)
                print("value: ", value)
                cls._fields[key] = value

    def sayHi(cls):
        print("Hi")


class TypeCheck(object):
    __metaclass__ = TypeCheckMeta

    def __setattr__(self, key, value):
        print("TypeCheck __setattr__")
        if key in self._fields:
            if not self._fields[key].is_valid(value):
                raise TypeError("Invalid type for field")
        super(TypeCheck, self).__setattr__(key, value)


class MetaTest(TypeCheck):
    print("MetaTest begin")
    name = TypeSetter(str)
    num = TypeSetter(int)
    print("MetaTest over")


if __name__ == "__main__":
    print("__main__ begin")
    mt = MetaTest()
    mt.name = "apple"
    MetaTest.sayHi()
    mt.sayHi()
    mt.num = "test"
