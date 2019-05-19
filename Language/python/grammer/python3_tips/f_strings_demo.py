#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Sun 19 May 2019 08:56:43 PM CST

user = "Jane Doe"
action = "buy"
log_message = 'User {} has logged in and did an action {}.'.format(
  user,
  action
)
print(log_message)
# User Jane Doe has logged in and did an action buy.


user = "Jane Doe"
action = "buy"
log_message = f'User {user} has logged in and did an action {action}.'
print(log_message)
# User Jane Doe has logged in and did an action buy.
