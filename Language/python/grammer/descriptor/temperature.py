#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 22 Jun 2018 06:48:34 PM CST

class Celsius:
    def __get__(self, instance, owner):
        return 5 * (instance.fahrenheit - 32) / 9

    def __set__(self, instance, value):
        instance.fahrenheit = 32 + 9 * value / 5


class Temperature:
    celsius = Celsius()

    def __init__(self, initial_f):
        self.fahrenheit = initial_f


t = Temperature(212)
print(t.celsius)
t.celsius = 0
print(t.fahrenheit)
