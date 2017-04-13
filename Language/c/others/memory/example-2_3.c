/*PS:使用malloc()，特别要留意heap段中的内存不用时，尽早手工free()。
 * 通过top输出的VIRT和RES两值来观察进程占用VM和RAM大小。*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char data_var  = '1';
char *mem_killer()
{
    char *p;

    p = (char *)malloc(1024*1024*4);
    memset(p, '\0', 1024*1024*4);
    p = &data_var;   //危险，内存泄露

    return p;
}

int main(int argc, char *argv[])
{
    char *p;
    for (;;)
    {
        p = mem_killer(); // 函数中malloc()分配的内存没办法free()
        printf("%c\n", *p);
        sleep(20);
    }

    return 0;
}


