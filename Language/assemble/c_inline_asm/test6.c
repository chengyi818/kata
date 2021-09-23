#include <stdio.h>


int main()
{
    int data1 = 1;
    int data2 = 2;
    int data3;

    asm("addl %1, %2\n\t"
        "movl %2, %0"
        : "=r"(data3)
        : "r"(data1),"r"(data2));

    printf("data3 = %d \n", data3);
    return 0;
}
