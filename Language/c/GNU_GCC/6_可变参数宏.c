/*
 * File Name: 6_可变参数宏.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 02:24:31 PM CST
 */
#include <stdio.h>

#define my_print(fmt, ...) \
    printf(fmt, ##__VA_ARGS__)

// __VA_ARGS__: 编译器保留参数

int main() {
    my_print("%d\n", 1);

    return 0;
}
