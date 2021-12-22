#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>

__thread int var = 0;   // var定义为线程变量，每个数线拥有一份

void* task_entry(void* arg);

int main()
{
    pthread_t pid1, pid2;

    pthread_create(&pid1, NULL, task_entry, (void *)1);
    pthread_create(&pid2, NULL, task_entry, (void *)2);

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    return 0;
}

void* task_entry(void* arg)
{
    int idx = (int)arg;
    int i;
    for (i = 0; i < 5; ++i)
    {
        printf("thread:%d  var = %d\n", idx, var += idx); // 每个线程只访问自己独享的那份
        sleep(1);
    }
}
