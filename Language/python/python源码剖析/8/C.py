a = 1
def f(a):
    # a = 2
    def g():
        print(a)

    # locals()
    return g

func = f(2)
func()
