#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 18 Jan 2018 02:45:47 PM CST

import atexit
import os
import readline
import rlcompleter
import sys

# tab completion
readline.parse_and_bind('tab: complete')
# history file
histfile = os.path.join(os.environ['HOME'], '.pythonhistory')
try:
    readline.read_history_file(histfile)
except IOError:
    pass
atexit.register(readline.write_history_file, histfile)

del os, histfile, readline, rlcompleter
