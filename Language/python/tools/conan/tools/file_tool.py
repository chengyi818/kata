#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 05 Feb 2020 03:53:10 PM CST

import os

def get_filelist(path):
    Filelist = []

    for home, dirs, files in os.walk(path):
        for filename in files:
            # 文件名列表，包含完整路径
            Filelist.append(os.path.join(home, filename))
            # 文件名列表，只包含文件名
            # Filelist.append( filename)
 
    return Filelist
