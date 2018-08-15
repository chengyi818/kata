#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }\
    while (0)\

int main(void)
{
    pid_t pid;
    printf("before calling fork,calling process pid = %d\n",getpid());
    pid = fork();
    if(pid == -1)
        ERR_EXIT("fork error");
    if(pid == 0){
        printf("this is child process and child's pid = %d,parent's pid = %d\n",getpid(),getppid());
    }
    if(pid > 0){
        //sleep(1);
        printf("this is parent process and pid =%d ,child's pid = %d\n",getpid(),pid);
    }

    return 0;
}
