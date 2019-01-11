#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 28 Nov 2017 04:23:29 PM CST

# 在创建类的时候,验证

class ValidatePolygon(type):
    def __new__(meta, name, bases, class_dict):
        # Don't validate the abstract Polygon class
        if bases != (object,):
            if class_dict['slides'] < 3:
                raise ValueError("Polygon need 3+ slides")
        return type.__new__(meta, name, bases, class_dict)


class Polygon(object, metaclass=ValidatePolygon):
    slides = None  # Specified by subclass

    @classmethod
    def interior_angles(cls):
        return (cls.slides - 2)*180


class Triangle(Polygon):
    slides = 3


class Line(Polygon):
    slides = 1
