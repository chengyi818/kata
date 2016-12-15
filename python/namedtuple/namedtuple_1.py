#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
from collections import namedtuple

human = namedtuple('human', ['name', 'height', 'age', 'sex'])

h = human('James', 180, 32, 0)

print("name:", h.name)
