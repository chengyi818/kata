def h():
    try:
        1/0
    finally:
        print("call h()")

def g():
    h()

def f():
    g()

f()
