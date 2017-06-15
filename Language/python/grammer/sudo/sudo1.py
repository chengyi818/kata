#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 15 Jun 2017 03:37:53 PM CST
import os

sudoPassword = input(">>> sudoPassword: ")
command = 'touch test'
total_command = "echo {0} | sudo -S {1}".format(sudoPassword, command)
p = os.system(total_command)
print(p)
