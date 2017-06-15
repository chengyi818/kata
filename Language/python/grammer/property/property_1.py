#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

class Resistor(object):
    def __init__(self, ohms):
        self.ohms = ohms
        self.voltage = 0
        self.current = 0

class BoundedResistance(Resistor):
    def __init__(self, ohms):
        super().__init__(ohms)
        self._ohms = 0

    @property
    def ohms(self):
        print("property ohms run")
        return self._ohms

    @ohms.setter
    def ohms(self, ohms):
        print("ohms setter run")
        if ohms <= 0:
            raise ValueError('%f ohms must be > 0' % ohms)
        self._ohms = ohms
        print("self._ohms: ", self._ohms)

R3 = BoundedResistance(1)
print(R3.__dict__)
print(BoundedResistance.__mro__)
# print(R3.ohms)
# print(R3._ohms)
# R3.ohms = 2
# print(R3.ohms)
# print(R3._ohms)
