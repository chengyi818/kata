# -*- coding: utf-8 -*-
"""
1. 类的data descriptor
2. 对象的attr
3. error
"""


class non_data_descriptor(list):
    """
    self: non_data_descriptor的实例
    obj: class A的实例a
    cls: class A
    """
    def __get__(self, obj, cls):
        # print("self", self)
        # print("obj", obj)
        # print("cls", cls)
        return "non_data_descriptor.__get__"


class data_descriptor(list):
    def __get__(self, obj, cls):
        # print("self", self)
        # print("obj", obj)
        # print("cls", cls)
        return "data_descriptor.__get__"

    def __set__(self, obj, value):
        print("self", self)
        print("obj", obj)
        print("cls", value)
        return "data_descriptor.__set__"


class A(object):
    # 1
    # value = data_descriptor()

    # value = non_data_descriptor()
    # value = "class_attr"

    def __init__(self):
        # 2
        self.value = "object_attr"
        pass


if __name__ == "__main__":
    a = A()
    a.value = 1
