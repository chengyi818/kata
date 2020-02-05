#!/usr/bin/env python3
# Author: ChengYi
# Mail: chengyi818@foxmail.cn
# created time: Wed 05 Feb 2020 03:01:51 PM CST
import os
import argparse
import logging
import json

from hashlib import md5
import clang.cindex
from clang.cindex import Config
from clang.cindex import Cursor
from clang.cindex import CursorKind

from base import const
from tools import file_tool

Config.set_library_file("/usr/lib/llvm-6.0/lib/libclang.so.1")
SOURCE_DIRECTORY = None

def parse_args():
    # parse args
    parser = argparse.ArgumentParser()
    parser.add_argument("--directory", "-d", dest="source_directory",
                        type=str, help="source directory")
    args = parser.parse_args()
    return args.source_directory

def get_json_lists():
    current_path = os.path.dirname(os.path.abspath(__file__))
    cases_path = os.path.join(current_path, const.CASES_PATH_NAME)
    logging.debug("cases_path: {}".format(cases_path))
    file_lists = file_tool.get_filelist(cases_path)

    return file_lists

def cve_checks(json_file_list):
    task_result = {}
    for json_file in json_file_list:
        if not json_file.endswith(".json"):
            return None

        with open(json_file, 'r') as f:
            case_info = json.load(f)
            logging.debug(case_info)

            case_result = patch_check(case_info)

            if case_result:
                task_result[case_info['cve_id']] = case_result

    return task_result

def get_token_list(node):
    token_list = []
    ts = node.get_tokens()
    for t in ts:
        #logging.debug("{} : {}".format(t.kind.name, t.spelling))
        if "COMMENT" not in t.kind.name:
            token_list.append(t.spelling)
    return token_list

def get_function_tokens(file_path, function_name):
    index = clang.cindex.Index.create()
    file_abspath = os.path.join(SOURCE_DIRECTORY, file_path)
    logging.debug("file_abspath: {}".format(file_abspath))
    tu = index.parse(file_abspath)
    for i in tu.cursor.get_children():
        if function_name in i.displayname:
            token_list = get_token_list(i)

    return token_list

def get_token_list_md5(tokens_list):
    s = md5()
    for c in tokens_list:
        s.update(c.encode())
    return s.hexdigest()
    

def patch_check(case_info):
    tokens_list = get_function_tokens(case_info['file_path'],
                        case_info['function_name'])
    logging.debug(tokens_list)
    cur_md5 = get_token_list_md5(tokens_list)
    logging.debug("cur_md5: {}".format(cur_md5))
    if cur_md5 in case_info["result_dict"]:
        return case_info['result_dict'][cur_md5]

    return "Unknown"

def main():
    global SOURCE_DIRECTORY
    SOURCE_DIRECTORY = parse_args()
    logging.debug("SOURCE_DIRECOTORY: {}".format(SOURCE_DIRECTORY))

    json_file_list = get_json_lists()
    logging.debug("json_file_lists: {}".format(json_file_list))

    task_result = cve_checks(json_file_list)
    # task_result = {"CVE_2016_2070": "PATCHED",
    #            "CVE_2019_20096": "PATCHED"}
    logging.info(task_result)


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    main()
