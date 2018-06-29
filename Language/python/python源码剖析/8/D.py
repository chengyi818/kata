a = 1

def g():
    print(a)

def f():
    print(a)
    a = 2
    print(a)

g()
f()

