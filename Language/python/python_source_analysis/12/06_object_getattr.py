# -*- coding: utf-8 -*-
"""
1. 类的data descriptor
2. 对象的attr
3. 类的non data descriptor
4. 类的attr
5. error
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
        # print("self", self)
        # print("obj", obj)
        # print("cls", value)
        return "data_descriptor.__set__"


class A(object):
    # 1
    # value = data_descriptor()
    # 3
    value = non_data_descriptor()
    # 4
    # value = "class_attr"

    def __init__(self):
        # 2
        self.value = "object_attr"
        pass


if __name__ == "__main__":
    a = A()
    print(a.value)
