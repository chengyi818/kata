def f():
    # raise Exception("I am a Exception")
    try:
        1/0
    except FileNotFoundError:
        pass


def g():
    try:
        f()
    except Exception:
        pass


g()
