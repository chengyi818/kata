/*
 * File Name: 2.typeof.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 01:49:58 PM CST
 */
#include <stdio.h>

int main() {
    int a = 0;
    typeof(a) b = a;

    printf("%d\n", b);

    return 0;
}
