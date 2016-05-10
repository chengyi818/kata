/*=============================================================================
#     FileName: integer_overflow_1.c
#         Desc: http://coolshell.cn/articles/11466.html
#       Author: ChengYi
#        Email: chengyi@antiy.cn
#     HomePage: http://www.antiy.com/
#      Created: 2016-05-10 11:50:50
#      Version: 0.0.1
#   LastChange: 2016-05-10 11:50:50
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/
#include <stdio.h>

int main(void)
{
    /*整型溢出举例*/
    unsigned char x = 0xff;
    printf("%d\n", ++x);

    signed char y =0x7f; //注：0xff就是-1了，因为最高位是1也就是负数了
    printf("%d\n", ++y);

    signed char m = 0x7f;
    signed char n = 0x05;
    signed char r = m * n;
    printf("%d\n", r);

    /*示例一:整型溢出导致死循环*/
    short len = 0;
    while(len< MAX_LEN) {
        len += readFromInput(fd, buf);
        buf += len;
    }

    /*示例二:整型转型时的溢出*/
    int copy_something(char *buf, int len)
    {
        #define MAX_LEN 256
        char mybuf[MAX_LEN];

        if(len > MAX_LEN){ // <---- [1]
            return -1;
        }

        return memcpy(mybuf, buf, len);
    }

    /*示例三：分配内存*/
    size_t nresp = packet_get_int();
    if (nresp > 0) {
        response = xmalloc(nresp*sizeof(char*));
        for (i = 0; i < nresp; i++)
            response[i] = packet_get_string(NULL);
    }

    /*示例四：缓冲区溢出导致安全问题*/
    int func(char *buf1, unsigned int len1,
            char *buf2, unsigned int len2 )
    {
        char mybuf[256];

        if((len1 + len2) > 256){    //<--- [1]
            return -1;
        }

        memcpy(mybuf, buf1, len1);
        memcpy(mybuf + len1, buf2, len2);

        do_some_stuff(mybuf);

        return 0;
    }

    /*示例五：size_t 的溢出*/
    for (int i= strlen(s)-1;  i>=0; i--)  { ... }
    for (int i=v.size()-1; i>=0; i--)  { ... }
}
