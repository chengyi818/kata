#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Sun 19 May 2019 09:16:46 PM CST

from enum import Enum, auto
class Monster(Enum):
    ZOMBIE = auto()
    WARRIOR = auto()
    BEAR = auto()
    
print(Monster.ZOMBIE)
# Monster.ZOMBIE

for monster in Monster:
    print(monster)
# Monster.ZOMBIE
# Monster.WARRIOR
# Monster.BEAR
