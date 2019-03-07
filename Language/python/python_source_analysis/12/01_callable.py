class A(object):
    def __call__(self):
        print("A called")

    def f(self):
        print("foo")


a = A()
a.f()
a()
