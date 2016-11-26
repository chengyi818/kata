#!/usr/bin/env python
# -*- coding: UTF-8 -*-
'''
# =============================================================================
#      FileName: sock_process.py
#          Desc:
#        Author: ChengYi
#         Email: chengyi@antiy.cn
#      HomePage: http://www.antiy.com/
#       Created: 2016-11-23 14:58:38
#       Version: 0.0.1
#    LastChange: 2016-11-23 14:58:38
#       History:
#                0.0.1 | ChengYi | init
# =============================================================================
'''

import multiprocessing
# import socket
import json
import Queue

class SocketProcess(multiprocessing.Process):
    def __init__(self, name, task_queue, result_queue):
        multiprocessing.Process.__init__(self)
        self.task_queue = task_queue
        self.result_queue = result_queue
        self.name = name
        self.server_host = 'localhost'
        self.server_port = 11010

    def run(self):
        # Establish socket connect
        # sockobj = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # sockobj.connect((self.server_host, self.server_port))
        while True:
            try:
                next_task = self.task_queue.get()
                if next_task is not None:

                    # sent Message to App
                    # json_data = SocketProcess.__prepare_json()
                    # sockobj.sendall(json_data)

                    print "%s: testing %s" % (self.name, next_task)
                    answer = next_task()
                    self.task_queue.task_done()
                    self.result_queue.put(answer)
            except Queue.Empty:
                print "queue empty"
        # sockobj.close()

    @staticmethod
    def __prepare_json():
        #"{"messageType":1, "caseName":"CVE_2016_0808", "caseType":"native"}";
        items_dic = {}
        items_dic["messageType"] = 1
        items_dic["caseName"] = "CVE_2016_0808"
        items_dic["caseType"] = "native"
        # encode to json string
        json_data = json.dumps(items_dic)
        return json_data
