#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Sun 19 May 2019 08:58:11 PM CST

from pathlib import Path
root = Path('post_sub_folder')
print(root)
# post_sub_folder
path = root / 'happy_user'
# Make the path absolute
print(path.resolve())
# /home/weenkus/Workspace/Projects/DataWhatNow-Codes/how_your_python3_should_look_like/post_sub_folder/happy_user
