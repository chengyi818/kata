# ceval.c
# PyEval_EvalCodeEx 1.1.6

def f(a=1, b=2):
    # tmp = 0
    print(a+b)


f()
f(b=3)
f(3)
