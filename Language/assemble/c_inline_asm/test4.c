#include <stdio.h>


int main()
{
    int data1 = 1;
    int data2 = 2;
    int data3;

    asm("movl %%ebx, %%eax\n\t"
        "addl %%ecx, %%eax"
        : "=a"(data3)
        : "b"(data1),"c"(data2));

    printf("data3 = %d \n", data3);
    return 0;
}
