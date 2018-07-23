count = 5


def A():
    global count

    def B():
        print("B")

    def C():
        print("enter C")
        global count
        while(count):
            count -= 1
            print("C")
            C()

    while(count):
        count -= 1
        print("A")
        A()
        C()


if __name__ == '__main__':
    A()
