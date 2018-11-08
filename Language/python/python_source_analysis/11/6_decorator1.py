def should_say(func1):
    def say():
        print("say somethin...")
        func1()

    return say


def func1():
    print("in func")


func1 = should_say(func1)
func1()
