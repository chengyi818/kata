#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

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
    fd = open("test.txt",O_RDWR);
    write(fd, "0123456789", 10);
    lseek(fd, 0, SEEK_SET);

    if(fd == -1)
        ERR_EXIT("OPEN ERROR");
    pid = fork();
    if(pid == -1)
        ERR_EXIT("fork error");
    if(pid == 0){
        write(fd,"child",5);
    } else if(pid > 0){
        sleep(3);
        char buf[10] = {0};
        read(fd, buf, 5);
        printf("buf: %s\n", buf);
    }

    return 0;
}
