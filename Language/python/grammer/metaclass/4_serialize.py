#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Tue 28 Nov 2017 04:42:39 PM CST
import json

registry = {}


class BetterSerializable(object):
    def __init__(self, *args):
        self.args = args

    def serialize(self):
        return json.dumps({
            'class': self.__class__.__name__,
            'args': self.args,
        })


def register_class(target_class):
    registry[target_class.__name__] = target_class


def deserialize(data):
    params = json.loads(data)
    name = params['class']
    target_class = registry[name]
    return target_class(*params['args'])


class Meta(type):
    def __new__(meta, name, bases, class_dict):
        cls = type.__new__(meta, name, bases, class_dict)
        register_class(cls)
        return cls


class RegisterSerializable(BetterSerializable, metaclass=Meta):
    pass


class Vector3D(RegisterSerializable):
    def __init__(self, x, y, z):
        super().__init__(x, y, z)
        self.x, self.y, self.z = x, y, z


if __name__ == "__main__":
    v3 = Vector3D(10, -7, 3)
    print("Before: ", v3)

    data = v3.serialize()
    print("Serialized: ", data)

    print("After: ", deserialize(data))
