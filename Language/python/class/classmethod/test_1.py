#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import os
from tempfile import TemporaryDirectory
from my_mapreduce_1 import mapreduce

def write_test_files(tmpdir):
    os.chdir(tmpdir)
    for i in range(20):
        file_name = "test{0}".format(i)
        my_str = "my_test{0}\n\n".format(i)
        with open(file_name, "w") as my_fp:
            my_fp.write(my_str)

def main():
    with TemporaryDirectory() as tmpdir:
        write_test_files(tmpdir)
        result = mapreduce(tmpdir)

    print('there are', result, ' lines')


if __name__ == '__main__':
    main()
