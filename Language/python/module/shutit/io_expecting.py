#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 30 Jun 2017 09:51:54 AM CST

import shutit

session = shutit.create_session('bash')

session.send('telnet', expect='elnet>', echo=True)

session.send('open baidu.com 80', expect='scape character', echo=True)

session.send('GET /', echo=True, check_exit=False)

session.logout()
