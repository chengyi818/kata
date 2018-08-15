/*
 * File Name: 9_内建函数const.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 02:51:41 PM CST
 */
#include <stdio.h>

int main() {
    const int a = 1;
    int b = 0;
    int ret;

    ret = __builtin_constant_p(a);
    printf("%d\n", ret);
    ret = __builtin_constant_p(b);
    printf("%d\n", ret);

    return 0;
}
