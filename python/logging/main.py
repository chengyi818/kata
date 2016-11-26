#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: main.py
#          Desc: accord debug level,print log
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-24 10:34:50
#       Version: 0.0.1
#    LastChange: 2016-11-24 10:34:50
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

from my_logging import MyLogging as logger

def main():
    logger.debug("debug test")
    logger.info("info test")
    logger.warning("warning test")
    logger.error("error test")

if __name__ == "__main__":
    main()
