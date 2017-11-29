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

    def __repr__(self):
        return("EvenBetterPoint2D({0})".format(self.args))


def register_class(target_class):
    registry[target_class.__name__] = target_class


def deserialize(data):
    params = json.loads(data)
    name = params['class']
    target_class = registry[name]
    return target_class(*params['args'])


class EvenBetterPoint2D(BetterSerializable):
    def __init__(self, x, y):
        super().__init__(x, y)
        self.x = x
        self.y = y


if __name__ == "__main__":
    # maybe forget
    register_class(EvenBetterPoint2D)

    point = EvenBetterPoint2D(5, 3)
    print("Before: ", point)

    data = point.serialize()
    print("Serialized: ", data)

    after = deserialize(data)
    print("After: ", after)
