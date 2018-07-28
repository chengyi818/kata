def should_say(fn):
    def say(*args):
        print("say somethin...")
        fn(*args)

    return say

def func1():
    print("in func")

func1 = should_say(func1)
func1()
