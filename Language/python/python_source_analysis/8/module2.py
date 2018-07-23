
# print("module2 locals id: ", id(locals()))
# print("module2 globals id: ", id(globals()))

def show_owner():
    # print("show_owner globals id: ", id(globals()))
    # print("show_owner locals id: ", id(locals()))
    print(owner)

owner = 'module2'
