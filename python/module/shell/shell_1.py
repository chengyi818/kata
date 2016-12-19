#!/usr/bin/env python

import commands

cmd = '
echo "hello world"
'



(status, output) = commands.getstatusoutput(cmd)
if status == 0:
    print output
else:
    print "error"
