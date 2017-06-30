#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 22 May 2017 11:27:02 AM CST

"""
The script is used to check all device environment
"""

import time
import argparse
import subprocess
from Mario.mario_bvds import bvds_check_env
from Mario.mario_bvds import bvds_get_case_list
from Mario.mario_bvds import bvds_test_and_get_result
from Mario.mario_bvds import bvds_clean_device
from Mario.mario_interface.mario_event import IMrEvent
from Mario.mario_utils.mario_log import MrLog

RELEASE_DIRECTORY = '/home/chengyi/temp/release'
LOG_DIRECTORY = '/home/chengyi/temp/log'
serial_num_list = []

parser = argparse.ArgumentParser(description='bvds test demo')
parser.add_argument('-c', '--cases',
                    default=[],
                    type=str,
                    nargs='+',
                    help='The cases to run.',
                    dest='cases')
parser.add_argument('-s', '--serial',
                    default=None,
                    type=str,
                    help='deivce serial number',
                    dest='serial')

args = parser.parse_known_args()


def get_device_serial_list():
    cmd = 'adb devices'
    (status, output) = subprocess.getstatusoutput(cmd)
    if status == 0:
        # get serial_num_list
        split_lines = output.split('\n')
        split_lines.pop(0)
        serial_num_list = []
        for line in split_lines:
            if 'device' in line and 'devices' not in line:
                serial_num_tmp_list = [x for x in line.split('\t')
                                       if len(x) > 0]
                serial_num_list.append(serial_num_tmp_list[0])

        return serial_num_list
    else:
        return None


if __name__ == "__main__":
    serial_num_list = get_device_serial_list()
    print(serial_num_list)
    for serial_num in serial_num_list:
            print("begin clean device")
            if bvds_clean_device(serial_num=serial_num,
                                 release_directory=RELEASE_DIRECTORY,
                                 log_directory=LOG_DIRECTORY,
                                 precheck=False,
                                 adb_cmd=None):
                print("serial_num: ", serial_num, "clean device OK")
