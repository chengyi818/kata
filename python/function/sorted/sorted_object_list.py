#!/usr/bin/env python3
# encoding=utf-8

class Case(object):
    def __init__(self, name, value):
        self.name = name
        self.value = value

def main():
    case_list = list()
    case_list.append(Case('A', 1))
    case_list.append(Case('C', 3))
    case_list.append(Case('B', 2))

    for case in case_list:
        print("before case name: ", case.name, "case value: ", case.value)

    case_list = sorted(case_list, key=lambda case: case.value)
    # case_list.sort(key=lambda case: case.value)

    for case in case_list:
        print("after case name: ", case.name, "case value: ", case.value)

if __name__ == "__main__":
    main()
