# -*- coding: utf-8 -*-
"""
1. 元类的data descriptor
2. 类的descriptor
3. 类的attr
4. 元类的non data descriptor
5. 元类的attr
6. error
"""


class non_data_descriptor(list):
    """
    self: non_data_descriptor的实例
    obj: class A的实例a
    cls: class A
    """
    def __get__(self, obj, cls):
        print("self", self)
        print("obj", obj)
        print("cls", cls)
        return "non_data_descriptor.__get__"


class data_descriptor(list):
    def __get__(self, obj, cls):
        print("self", self)
        print("obj", obj)
        print("cls", cls)
        return "data_descriptor.__get__"

    def __set__(self, obj, value):
        # print("self", self)
        # print("obj", obj)
        # print("cls", value)
        return "data_descriptor.__set__"


class Meta(type):
    # 1
    # value = data_descriptor()
    # 4
    value = non_data_descriptor()
    # 5
    # value = "metaclass_attr"

    def __new__(meta, name, bases, class_dict):
        return type.__new__(meta, name, bases, class_dict)

    def __init__(meta, name, bases, class_dict):
        return type.__init__(meta, name, bases, class_dict)

    def __call__(cls, *args, **kwargs):
        instance = type.__call__(cls, *args, **kwargs)
        return instance


class A(object):
    __metaclass__ = Meta

    # 2
    value = data_descriptor()
    # 2
    # value = non_data_descriptor()
    # 3
    # value = "class_attr"


if __name__ == "__main__":
    print(A.value)
