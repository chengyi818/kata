#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

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
    int fd;
    fd = open("test.txt",O_WRONLY);
    if(fd == -1)
        ERR_EXIT("OPEN ERROR");
    pid = fork();
    if(pid == -1)
        ERR_EXIT("fork error");
    if(pid == 0){
        write(fd,"child",5);
    }
    if(pid > 0){
        //sleep(1);
        write(fd,"parent",6);
    }

    return 0;
}
