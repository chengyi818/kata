#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: mixin_1.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-12-12 22:23:45
#       Version: 0.0.1
#    LastChange: 2016-12-12 22:23:45
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

class People(object):
    def __init__(self, *, name):
        self.name = name

    def make_tea(self):
        teapot = self.get_teapot()
        teapot.put_in_tea()
        teapot.put_in_water()
        return teapot

    def get_teapot(self):
        return Teapot(self.name)


class Teapot(object):
    def __init__(self, name):
        self.name = name

    def put_in_tea(self):
        print("{0} teapot put in tea".format(self.name))

    def put_in_water(self):
        print("{0} teapot put in water".format(self.name))

    def drink(self):
        print("drink {0} teapot".format(self.name))




def main():
    people = People(name='common')
    my_teapot = people.get_teapot()
    my_teapot.drink()


if __name__ == '__main__':
    main()
