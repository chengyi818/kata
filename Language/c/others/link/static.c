/*
 * File Name: static.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Mon 03 Jul 2017 03:14:04 PM CST
 */
#include <stdio.h>
#include "static.h"

const char* static_str = "I'm a static str.";

void print_static_str()
{
    printf("%s\n", static_str);
}
