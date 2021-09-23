#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: mario_const.py
#          Desc: Define constant class
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-28 10:53:34
#       Version: 0.0.1
#    LastChange: 2016-11-28 10:53:34
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''


class MrConst(object):
    # pylint: disable=too-few-public-methods
    class ConstError(TypeError):
        pass

    class ConstCaseError(ConstError):
        pass

    def __setattr__(self, key, value):
        if self.__dict__.has_key(key):
            raise self.ConstError("Can't change const.{0}!".format(key))
        if not key.isupper():
            raise self.ConstCaseError(
                ("cosnt name '{0}' is not all uppercase!".format(key)))
        self.__dict__[key] = value


import sys

sys.modules[__name__] = MrConst()
print(3)
