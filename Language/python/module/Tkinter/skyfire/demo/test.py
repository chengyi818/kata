#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Mon 22 May 2017 11:27:02 AM CST

import os
import time
import datetime
import shutil
import subprocess
import traceback
from Mario.mario_bvds import bvds_test_and_get_result
from Mario.mario_utils.mario_adb import MrAdb
from Mario.mario_utils.mario_log import MrLog

RELEASE_DIRECTORY = '/home/chengyi/temp/release'
LOG_DIRECTORY = '/home/chengyi/temp/log'
TARGET_DIR = "/home/chengyi/temp/log_classified"

MARIO_ABNORMAL = "1_mario_abnormal"
CASE_ABNORMAL = "2_case_abnormal"
CASE_INSTABILITY = "3_case_instability"
MARIO_LOG = "mario_log.txt"
MARIO_NORMAL = "Mario正常退出"
MARIO_EXIT_MANUAL = "Mario手动退出"

MARIO_NORMAL_STR = "Mario exit normally"
CASE_INSTABILITY_STR = "Result Check type: Result Instability"
CASE_ABNORMAL_STR = "Result Check type: Result Abnormal"
MANUAL_END_STR = "catch ctrl+c"
serial_num_list = []
CASE_LIST = []
LOG_LEVEL = 'warning'


def wait_device(serial_num):
    wait_time = 0
    while not MrAdb.is_device_ready(serial_num):
        time.sleep(1)
        wait_time += 1
        MrLog.debug("wait_time: {0} s".format(wait_time))

    MrLog.debug("device found")


def reboot_device(serial_num):
    MrAdb.reboot_device(serial_num)
    wait_device(serial_num)


def log_classify():
    MARIO_ABNORMAL_PATH = os.path.join(TARGET_DIR, MARIO_ABNORMAL)
    CASE_ABNORMAL_PATH = os.path.join(TARGET_DIR, CASE_ABNORMAL)
    CASE_INSTABILITY_PATH = os.path.join(TARGET_DIR, CASE_INSTABILITY)
    for name in [MARIO_ABNORMAL_PATH,
                 CASE_ABNORMAL_PATH,
                 CASE_INSTABILITY_PATH]:
        if not os.path.exists(name):
            os.makedirs(name)

    dir_path_list = []
    list = os.listdir(LOG_DIRECTORY)
    for line in list:
        filepath = os.path.join(LOG_DIRECTORY, line)
        if os.path.isdir(filepath):
            dir_path_list.append(filepath)

    for dir_path in dir_path_list:
        mario_log_path = os.path.join(dir_path, MARIO_LOG)
        if not os.path.isfile(mario_log_path):
            return
        else:
            print("mario_log_path: ", mario_log_path)

        task_tag_list = []
        with open(mario_log_path) as file_handle:
            for line in file_handle:
                if MARIO_NORMAL_STR in line:
                    task_tag_list.append(MARIO_NORMAL)
                if CASE_ABNORMAL_STR in line:
                    task_tag_list.append(CASE_ABNORMAL)
                if CASE_INSTABILITY_STR in line:
                    task_tag_list.append(CASE_INSTABILITY)
                if MANUAL_END_STR in line:
                    task_tag_list.append(MARIO_EXIT_MANUAL)

        print("task_tag_list: ", task_tag_list)

        if MARIO_EXIT_MANUAL in task_tag_list:
            print("Exit manually, remove log")
            shutil.rmtree(dir_path)
        elif MARIO_NORMAL not in task_tag_list:
            print("mario abnormal, move to: ", MARIO_ABNORMAL_PATH)
            shutil.move(dir_path, MARIO_ABNORMAL_PATH)
        elif CASE_ABNORMAL in task_tag_list:
            print("case abnormal, move to: ", CASE_ABNORMAL_PATH)
            shutil.move(dir_path, CASE_ABNORMAL_PATH)
        elif CASE_INSTABILITY in task_tag_list:
            print("case instability, move to: ", CASE_INSTABILITY_PATH)
            shutil.move(dir_path, CASE_INSTABILITY_PATH)
        elif MARIO_NORMAL in task_tag_list:
            print("everything fine, remove log")
            shutil.rmtree(dir_path)
        else:
            raise AttributeError(
                "unkown mario.log: {0}".format(mario_log_path))
        print("\n")


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


def device_battery_enough(serial_num):
    cmd = ("adb -s {0} shell dumpsys battery".format(serial_num))
    (status, output) = subprocess.getstatusoutput(cmd)
    if status != 0:
        return False
    lines = output.split('\n')
    battery_left = 0
    for line in lines:
        if "level" in line:
            battery_left = max(int(line.split()[1]), battery_left)

    print("battery_left: ", battery_left)
    if battery_left < 10:
        return False
    else:
        return True


if __name__ == "__main__":
    if os.path.isfile("test.log"):
        os.remove("test.log")
    serial_num_list = get_device_serial_list()
    print(serial_num_list)
    for loop_id in range(0, 10000):
        for serial_num in serial_num_list:
            time.sleep(10)
            if not device_battery_enough(serial_num):
                print("Device serial_num: {0} not enough battery".format(
                    serial_num))
                continue

            print("Device serial_num: {0} loop_id: {1} begin".format(serial_num,
                                                                     loop_id))
            try:
                RESULT = bvds_test_and_get_result(
                    case_list=CASE_LIST,
                    serial_num=serial_num,
                    adb_cmd=None,
                    precheck=False,
                    result_check=True,
                    filter_type=["all"],
                    log_level=LOG_LEVEL,
                    release_directory=RELEASE_DIRECTORY,
                    log_directory=LOG_DIRECTORY
                )
            except Exception as e:
                print("loop_id: {0}, Catch Exception: {1}".format(loop_id, e))
                with open('test.log', "a") as file_handle:
                    traceback.print_stack(file=file_handle)
                    file_handle.write(
                        "serial_num: {0} loop_id: {1}, "
                        "Catch Exception: {2}\n".format(
                            serial_num, loop_id, e))

            with open('test.log', "a") as file_handle:
                file_handle.write(
                    "{2} serial_num: {0} loop_id: {1} run over\n".format(
                        serial_num, loop_id, datetime.datetime.now()))
            # reboot_device(serial_num)


            log_classify()
