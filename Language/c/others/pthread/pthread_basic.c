/*
 * File Name: pthread_basic.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 09 Mar 2018 01:54:56 PM CST
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *thread_fun1(void *arg) {
    srand((unsigned)time(NULL));
    printf("enter thread_fun1: %d\n", rand()%2);

    pthread_exit(NULL);
}


int main(void) {
    pthread_t pthread_id;

    pthread_create(&pthread_id, NULL, thread_fun1, NULL);

    pthread_join(pthread_id, NULL);

    return 0;
}
