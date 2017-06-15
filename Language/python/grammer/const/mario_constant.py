#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os
import logging
from . import mario_const

# basic
mario_const.CURRENT_PATH = os.path.dirname(__file__)
mario_const.APP_DIRECTORY = 'app'
mario_const.APP_FILE_NAME = 'app-debug.apk'
mario_const.MAX_TOKEN_RANDOM = 0x7FFFFFFF

# database
mario_const.SQLITE3DB_DIRECTORY = 'db'
mario_const.SQLITE3DB_FILE_NAME = 'wqdb.db'

# log level
# DEBUG INFO WARNING ERROR
mario_const.DEBUG_LEVEL = logging.DEBUG

# config
mario_const.DEFAULT_CONFIG = 'mario.cfg'

#App
mario_const.APK_NAME = 'com.weiqing.wheeljack'
mario_const.ACTIVITY_NAME = 'MainActivity'
mario_const.REBOOT_TIME = 60 #second

#Test Level
mario_const.TESTLEVEL_NOCRASH = 0
mario_const.TESTLEVEL_OTHER_PROCESS_CRASH = 1
mario_const.TESTLEVEL_SELF_PROCESS_CRASH = 2
mario_const.TESTLEVEL_SYSTEM_CRASH = 3
mario_const.TESTLEVEL_DEFAULT = 2

#Protocal
mario_const.TYPE_SHAKE_HAND = 0
mario_const.TYPE_PRETEST = 1
mario_const.TYPE_DESCRIPTION = 2
mario_const.TYPE_STARTBLOCK = 3
mario_const.TYPE_RESULT = 4
mario_const.TYPE_CONFIRM = 5
mario_const.TYPE_CASE_ERROR = 6
mario_const.TYPE_SEQUENCE_ERROR = 7
mario_const.TYPE_CASE_OVER = 8

mario_const.TIMEOUT_SHAKE_HAND = 3 #second
mario_const.TIMEOUT_PRETEST = 3 #second
mario_const.TIMEOUT_DESCRIPTION = 5 #second
mario_const.TIMEOUT_STARTBLOCK = 5 #second
mario_const.TIMEOUT_CASE_OVER = 3 #second

mario_const.LOCAL_PORT = 11010
mario_const.DEVICE_PORT = 42178


mario_const.CONFIG_FILE_TEMPLATE = '''

*********************************************

Template:
#Config file for mario
[mario]
release_directory = [release directory path]

*********************************************

Example:
#Config file for mario
[mario]
release_directory = /home/sphantix/test/release

'''
