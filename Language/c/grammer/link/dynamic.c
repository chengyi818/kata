/*
 * File Name: dynamic.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Mon 03 Jul 2017 03:24:06 PM CST
 */

#include <stdio.h>
#include "static.h"
#include "dynamic.h"

const char* dynamic_str = "I'm a dynamic str";
void print_dynamic_str() {
    /* print_static_str(); */
    printf("%s\n", dynamic_str);
}
