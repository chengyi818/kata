import sys

value = 3


def g():
    frame = sys._getframe()
    print("current funcion is: ", frame.f_code.co_name)
    print("current local id: ", id(frame.f_locals), "content: ", frame.f_locals)
    print("current global id: ", id(frame.f_globals), "content: ", frame.f_globals)
    # print("current co_flags is: ", frame.f_code.co_flags)

    print("----------------------------------------------------------------------")

    caller = frame.f_back
    print("caller function is: ", caller.f_code.co_name)
    print("caller local id: ", id(caller.f_locals), "content: ", caller.f_locals)
    print("caller global id: ", id(caller.f_globals), "content: ", caller.f_globals)


def f():
    a = 1
    b = 2
    g()


def show():
    f()


show()
