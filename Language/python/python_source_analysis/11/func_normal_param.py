# import dis

def f(name, age):
    test = 1
    age += 5
    print("name: ", name, "age: ", age)


f("Robert", age=5)
# dis.dis(f)

