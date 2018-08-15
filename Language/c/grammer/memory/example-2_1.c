/* @filename: example-2.c */

/*PS:变量p，它在Stack段，但它所指的”hello world”是一个字符串直接量，放在Text段。*/
#include <stdio.h>


int main(int argc, char *argv[])
{

    char arr[] = "hello world"; /* Stack段，rw--- */

    char *p = "hello world chengyi";        /* Text段，字符串直接量, r-x--  */

    arr[1] = 'l';

    *(++p) = 'l';   /* 出错了,Text段不能write */

    return 0;
}

