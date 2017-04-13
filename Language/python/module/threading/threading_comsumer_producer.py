#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import queue
import threading
import random

WRITELOCK = threading.Lock()

class Producer(threading.Thread):

