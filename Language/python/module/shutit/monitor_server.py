#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 30 Jun 2017 09:50:29 AM CST

import shutit

capacity_command = """df / | awk '{print $5}' | tail -1 | sed s/[^0-9]//"""

session1 = shutit.create_session('bash')
session2 = shutit.create_session('bash')

password1 = session1.get_input('Password for server1', ispass=True)
password2 = session2.get_input('Password for server2', ispass=True)

session1.login('ssh you@one.example.com', user='you', password=password1)
session2.login('ssh you@two.example.com', user='you', password=password2)

capacity = session1.send_and_get_output(capacity_command)
if int(capacity) < 10:
    print('RUNNING OUT OF SPACE ON server1!')

capacity = session2.send_and_get_output(capacity_command)
if int(capacity) < 10:
    print('RUNNING OUT OF SPACE ON server2!')

session1.logout()
session2.logout()
