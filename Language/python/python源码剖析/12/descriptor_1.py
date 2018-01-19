"""
descriptor改变返回值
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
    print(b.value)
