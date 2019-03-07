# -*- coding: utf-8 -*-


class A(object):
    @staticmethod
    def foo():
        print("foo")

    def bar(self):
        print("bar")


if __name__ == "__main__":
    a = A()
    a.foo()
    A.foo()
    print(a.foo)
    print(A.foo)
    print(a.bar)
    print(A.bar)
    # print(A.__dict__['foo'])
