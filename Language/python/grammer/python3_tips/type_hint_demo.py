#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Sun 19 May 2019 09:15:12 PM CST

def sentence_has_animal(sentence: str) -> bool:
    ret = "animal" in sentence
    print(ret)

    return ret

sentence_has_animal("Donald had a farm without animals")
# True
