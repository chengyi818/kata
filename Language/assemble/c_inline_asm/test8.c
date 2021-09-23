#include <stdio.h>


int main()
{
    int data1 = 1;
    int data2 = 2;
    int data3;

    asm("movl %1, %%eax\n\t"
        "addl %2, %%eax\n\t"
        "movl %%eax, %0"
        : "=m"(data3)
        : "m"(data1),"m"(data2));

    printf("data3 = %d \n", data3);
    return 0;
}
