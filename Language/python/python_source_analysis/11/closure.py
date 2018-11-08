def get_func():
    value = "inner"
    print(value)

    def inner_func():
        print(value)

    return inner_func


show_value = get_func()
show_value()
