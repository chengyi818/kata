class MyInt(int):
    def __add__(self, other):
        return int.__add__(self, other) + 10


a = MyInt(1)
b = MyInt(2)

print(a+b)
