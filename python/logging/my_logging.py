#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import logging

class MyLogging(object):
    DEBUG_LEVEL = logging.ERROR

    @staticmethod
    def debug(data):
        logging.basicConfig(level=MyLogging.DEBUG_LEVEL,
                        format='%(asctime)s %(levelname)s %(message)s',
                        datefmt='%a, %d %b %Y %H:%M:%S'
                        )
        logging.debug(data)

    @staticmethod
    def info(data):
        logging.basicConfig(level=MyLogging.DEBUG_LEVEL,
                        format='%(asctime)s %(levelname)s %(message)s',
                        datefmt='%a, %d %b %Y %H:%M:%S'
                        )
        logging.info(data)

    @staticmethod
    def warning(data):
        logging.basicConfig(level=MyLogging.DEBUG_LEVEL,
                        format='%(asctime)s %(levelname)s %(message)s',
                        datefmt='%a, %d %b %Y %H:%M:%S'
                        )
        logging.warning(data)

    @staticmethod
    def error(data):
        logging.basicConfig(level=MyLogging.DEBUG_LEVEL,
                        format='%(asctime)s %(levelname)s %(message)s',
                        datefmt='%a, %d %b %Y %H:%M:%S'
                        )
        logging.error(data)
