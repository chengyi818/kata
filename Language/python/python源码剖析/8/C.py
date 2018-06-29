a = 1
def f():
    a = 2
    def g():
        print(a)
    return g

func = f()
func()
