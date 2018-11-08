def h():
    try:
        a = 1/0
    except ZeroDivisionError:
        print(a)
    finally:
        print("call h()")


def g():
    h()


def f():
    g()


f()
