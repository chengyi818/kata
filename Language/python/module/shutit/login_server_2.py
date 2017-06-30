#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 30 Jun 2017 09:48:29 AM CST

import shutit

session = shutit.create_session('bash')

password = session.get_input('', ispass=True)

session.login('ssh you@example.com', user='you',
              password=password)

session.send('hostname', echo=True)

session.logout()
