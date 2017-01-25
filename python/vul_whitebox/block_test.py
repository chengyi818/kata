#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os

#project info which set by user
PROJECT_INFO_DICT_A = {'android_version': '5.1.1',
                       'android_source': '/home/chengyi/code/android_5.1.1_r14_mako'}
PROJECT_INFO_DICT_B = {'android_version': '6.0',
                       'android_source': '/home/chengyi/code/android_6.0_r26_bullhead'}
PROJECT_INFO_DICT_C = {'android_version': '6.0.1',
                       'android_source': '/home/chengyi/code/android_6.0.1_r22_bullhead'}
PROJECT_INFO_DICT = PROJECT_INFO_DICT_C



def code_preprocess(string):
    return string.replace(' ', '').replace('\n', '')

def block_test():
    file_relative_location_dict = {
        '5.1.1': 'frameworks/native/libs/gui/IGraphicBufferConsumer.cpp',
        '6.0': 'frameworks/native/libs/gui/IGraphicBufferConsumer.cpp',
        '6.0.1': 'frameworks/native/libs/gui/IGraphicBufferConsumer.cpp',
        'Default': 'frameworks/native/libs/gui/IGraphicBufferConsumer.cpp'
    }

    #Step 1: check file exist
    android_version = PROJECT_INFO_DICT['android_version']
    file_absolute_location = os.path.join(PROJECT_INFO_DICT['android_source'],
                                          file_relative_location_dict[android_version])
    if not os.path.isfile(file_absolute_location):
        print("file: {0} not exist".format(file_absolute_location))
        return False
    else:
        print("file: {0} exist".format(file_absolute_location))

    #Step 2: reduce scope
    upper_line = 'data.read(*buffer.get());'
    lower_line = 'reply->writeInt32(slot);'
    raw_code = ' '
    flag = False
    with open(file_absolute_location) as file_p:
        for line in file_p.readlines():
            if code_preprocess(line) == lower_line:
                break
            if code_preprocess(line) == upper_line:
                flag = True
            if flag:
                raw_code += line

    #Step 3: code preprocess
    print("raw_code:")
    print(raw_code)
    print('after code_preprocess:')
    print(code_preprocess(raw_code))

    #Step 4: compare with template
    vul_template = 'data.read(*buffer.get());intslot;intresult=attachBuffer(&slot,buffer);'
    patch_template = 'data.read(*buffer.get());intslot=-1;intresult=attachBuffer(&slot,buffer);'
    if code_preprocess(raw_code) == vul_template:
        print('Vulnerable')
    elif code_preprocess(raw_code) == patch_template:
        print('Patched')
    else:
        print('unknow')

if __name__ == '__main__':
    block_test()
