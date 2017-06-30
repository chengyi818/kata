#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 30 Jun 2017 09:54:20 AM CST

# 当脚本运行到暂停点时，同时按下“Ctrl”和“]”，则可以让脚本继续执行。
import shutit

session = shutit.create_session('bash')

session.pause_point('Have a look around!')

session.send('echo "Did you enjoy your pause point?"', echo=True)
