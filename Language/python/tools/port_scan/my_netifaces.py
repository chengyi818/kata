#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 18 Dec 2017 05:25:01 PM CST
import netifaces

x = netifaces.interfaces()

for i in x:
    print(netifaces.ifaddresses(i))

    print('\nInterface: ' + i)
    mac = netifaces.ifaddresses(i)[netifaces.AF_LINK][0]['addr']
    print('Mac addr: ' + mac)

    try:
        ip = netifaces.ifaddresses(i)[netifaces.AF_INET][0]['addr']

        print('IP addr: {0} '.format(ip))
    except KeyError:
        print('NO IP')
        continue
