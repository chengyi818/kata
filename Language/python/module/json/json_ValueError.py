#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import json
my_string = '{"uid":"1111111","method":"check_user"}\x00'

print(my_string)
print(repr(my_string))
print(json.loads(my_string))
