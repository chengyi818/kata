def should_say(fn):
    def say():
        print("say somethin...")
        fn()

    return say

@should_say
def func():
    print("in func")


func()
