# -*- coding: utf-8 -*-
"""
getatr
1. 类的data descriptor
2. 对象的attr
3. 类的non data descriptor
4. 类的attr
5. error

setattr
1. 类的data descriptor
2. 对象的attr
3. error
"""

"""
resistance * current = voltage
"""


class current_descriptor(list):
    def __get__(self, obj, cls):
        # print("self", self)
        # print("obj", obj)
        # print("cls", cls)
        return obj._current


class voltage_descriptor(list):
    def __get__(self, obj, cls):
        # print("self", self)
        # print("obj", obj)
        # print("cls", cls)
        return obj._voltage

    def __set__(self, obj, value):
        # print("self", self)
        # print("obj", obj)
        # print("cls", value)
        obj._voltage = value
        obj._current = (value/obj.resistance)


class electric(object):
    voltage = voltage_descriptor()
    current = current_descriptor()

    def __init__(self, resistance):
        self.resistance = resistance


if __name__ == "__main__":
    a = electric(10)
    a.voltage = 100

    print("voltage: ", a.voltage)
    print("current: ", a.current)

    b = electric(5)
    b.voltage = 30
    print("voltage: ", b.voltage)
    print("current: ", b.current)
