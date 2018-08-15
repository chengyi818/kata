/*
 * File Name: 5_标号元素.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 15 Aug 2018 02:15:49 PM CST
 */
#include <stdio.h>

struct student {
    int name;
    int score;
    /* int age; */
    int class;
};

int main() {
    struct student a = {
        .name = 1,
        .class = 2,
    };

    printf("%d %d %d\n", a.name, a.score, a.class);

    return 0;
}
