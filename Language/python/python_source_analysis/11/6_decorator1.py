def should_say(func1):
    def say():
        print("say something...")
        func1()

    return say


def func1():
    print("in func")

say = should_say(func1)

