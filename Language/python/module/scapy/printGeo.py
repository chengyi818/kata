#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 27 Nov 2017 04:12:55 PM CST

import pygeoip

gi = pygeoip.GeoIP("./GeoLiteCity.dat")


def printRecord(tgt):
    rec = gi.record_by_name(tgt)
    print(rec)
    # city = rec['city']
    # region = rec['region_name']
    # country = rec['country_name']
    # longitude = rec['longitude']
    # latitude = rec['latitude']
    # print("[*] Target: ", tgt, "Geo-located")
    # print("[+] ", city, region, country)
    # print("[+] ", longitude, latitude)


tgt = '173.255.226.98'
printRecord(tgt)
