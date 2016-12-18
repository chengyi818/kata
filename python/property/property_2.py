#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

class Resistor(object):
    def __init__(self, ohms):
        self.ohms = ohms
        self.voltage = 0
        self.current = 0

class MysteriousResistor(Resistor):
    @property
    def ohms(self):
        self.voltage = self._ohms * self.current
        return self._ohms

R7 = MysteriousResistor(10)
R7.current = 0.01
print(R7.voltage)
R7.ohms
print(R7.voltage)
