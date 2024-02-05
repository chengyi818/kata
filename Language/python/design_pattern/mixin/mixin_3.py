class MyMixin:
    def mixin_method(self):
        print("Mixin method called")


class MyClass(object):
    def my_method(self):
        print("My method called")


class MixedClass(MyClass, MyMixin):
    pass


mixed_instance = MixedClass()
mixed_instance.my_method()     # 输出 "My method called"
mixed_instance.mixin_method()  # 输出 "Mixin method called"
