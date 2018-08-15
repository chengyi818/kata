/*
 * File Name: 8_变量属性和类型属性.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 02:43:51 PM CST
 */
#include <stdio.h>


struct A {
    char name;
    int age[2] __attribute__((packed));
};

struct B {
    char name;
    int age[2];
};

int main() {
    printf("%lu\n", sizeof(struct A));
    printf("%lu\n", sizeof(struct B));

    return 0;
}
