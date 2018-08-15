/*
 * File Name: 4_case范围.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 02:08:01 PM CST
 */
#include <stdio.h>


int main() {
    int a = 1;

    switch(a) {
    case 1 ... 3:
        printf("1~3\n");
        break;
    default:
        printf("other\n");
    }

    char b = 'a';
    switch(b) {
    case 'a' ... 'z':
        printf("lowwer letter\n");
        break;
    case 'A' ... 'Z':
        printf("upper letter\n");
        break;
    default:
        printf("other\n");
    }

    return 0;
}
