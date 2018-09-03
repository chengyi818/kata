a = 1


def g():
    print(a)


def f():
    global a
    print(a)
    a = 2
    print(a)


g()
f()
g()
