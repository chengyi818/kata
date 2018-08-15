/*
 * File Name: 7_函数属性.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 02:32:01 PM CST
 */
// 不是很理解
#include <stdio.h>
int a;

int __attribute_const__ die(void) {
    return a;
}

int main() {
    a = 1;
    printf("%d\n", die());
    a = 2;
    printf("%d\n", die());
    return 0;
}
