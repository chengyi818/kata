"""
instance属性优于non data descriptor
"""


class A(list):
    """
    self: class A的实例value
    obj: class B的实例b
    cls: class B
    """
    def __get__(self, obj, cls):
        print("self", self)
        print("obj", obj)
        print("cls", cls)
        return "A.__get__"


class B(object):
    value = A()


if __name__ == "__main__":
    b = B()
    b.value = 1
    print(b.__dict__["value"])
    print(b.__class__.__dict__['value'])
