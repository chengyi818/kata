/*
 * File Name: test_so.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 12 Apr 2019 02:01:45 PM CST
 */

#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>

#include "test_so.h"

typedef void (*Hello)(char*);
Hello tptr;
#define LOG_BUF_SIZE 1024

void log_print(const char* fmt, ...) {
    va_list ap;
    char buf[LOG_BUF_SIZE];

    assert(fmt != NULL);

    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF_SIZE, fmt, ap);
    va_end(ap);

    printf("%s\n", buf);
    /* tptr(buf); */
    /* usleep(200); */
}

void *myThread(void* vargp) {
    long *myid = (long*)vargp;
    int i = 1000000;
    while(i--) {
        log_print("%ld", *myid);
    }

    return NULL;
}

//test_so.c
int test_so_func(void* ptr, int a,int b)
{
    tptr = (Hello)ptr;

    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id3;

    pthread_create(&thread_id1, NULL, myThread, (void*)&thread_id1);
    pthread_create(&thread_id2, NULL, myThread, (void*)&thread_id2);
    pthread_create(&thread_id3, NULL, myThread, (void*)&thread_id3);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    log_print("main thread exit");

    return a*b;
}
