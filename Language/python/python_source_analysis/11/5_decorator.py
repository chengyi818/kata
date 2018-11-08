def should_say(fn):
    def say():
        print("say somethin...")
        fn()

    return say


@should_say
def func1():
    print("in func")


func1()
