#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Fri 30 Jun 2017 09:56:13 AM CST
import shutit

import time

long_command = """sleep 60"""

session1 = shutit.create_session('bash')
session2 = shutit.create_session('bash')

password1 = session1.get_input('Password for server1', ispass=True)
password2 = session2.get_input('Password for server2', ispass=True)

session1.login('ssh you@one.example.com', user='you', password=password1)
session2.login('ssh you@two.example.com', user='you', password=password2)

start = time.time()

session1.send(long_command, background=True)
session2.send(long_command, background=True)

print('That took: ' + str(time.time() - start) + ' seconds to fire')

session1.wait()
session2.wait()

print('That took: ' + str(time.time() - start) + ' seconds to complete')
