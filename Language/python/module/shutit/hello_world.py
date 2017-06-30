#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 30 Jun 2017 09:39:13 AM CST


import shutit

session = shutit.create_session('bash')

session.send('echo Hello World', echo=True)
