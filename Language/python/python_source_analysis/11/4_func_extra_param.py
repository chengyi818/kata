def f(*arg, **kwargs):
    test = 2
    print(arg)
    print(kwargs)
    print(test)


f(1, 2)
f(b=3)
