/*
 * File Name: 3_零长数组.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 01:53:28 PM CST
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct A {
    int length;
    char content[0];
};


int main() {
    int length = 10;
    struct A *a = malloc(sizeof(struct A) + length);
    a->length = length;
    memset(a->content, 'a', length);

    for(int i=0; i<length; i++) {
        printf("%c ", a->content[i]);
    }

    free(a);
    return 0;
}
