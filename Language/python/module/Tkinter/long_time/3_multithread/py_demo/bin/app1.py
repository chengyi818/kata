#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Thu 29 Jun 2017 08:19:21 PM CST

import logging
import time
import gettext
_ = gettext.gettext


def calc():
    logger = logging.getLogger(__name__)
    for i in range(100, 0, -1):
        logger.info(_('Countdown value is %i'), i)
        time.sleep(0.2)

    logger.info(_('Done!'))


logging.basicConfig()
logging.getLogger().setLevel(logging.INFO)
calc()
