#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Sun 19 May 2019 09:21:23 PM CST

class Armor:
    def __init__(self, armor: float, description: str, level: int = 1):
        self.armor = armor
        self.level = level
        self.description = description
                 
    def power(self) -> float:
        return self.armor * self.level
    
armor = Armor(5.2, "Common armor.", 2)
armor.power()
# 10.4
print(armor)
# <__main__.Armor object at 0x7fc4800e2cf8>


from dataclasses import dataclass
@dataclass
class Armor:
    armor: float
    description: str
    level: int = 1
    
    def power(self) -> float:
        return self.armor * self.level
    
armor = Armor(5.2, "Common armor.", 2)
armor.power()
# 10.4
print(armor)
# Armor(armor=5.2, description='Common armor.', level=2)
