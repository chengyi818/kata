#include <stdio.h>


int main()
{
    int data1 = 1;
    int data2 = 2;
    int data3;

    asm("addl %[v1], %[v2]\n\t"
        "movl %[v2], %[v3]"
        : [v3]"=r"(data3)
        : [v1]"r"(data1),[v2]"r"(data2));

    printf("data3 = %d \n", data3);
    return 0;
}
