import module2

owner = 'module1'
print("module1 locals id: ", id(locals()))
print("module1 globals id: ", id(globals()))
module2.show_owner()
