#include <stdio.h>

int a = 1;
int b = 2;
int c;

int main()
{
    asm("movl a, %eax\n\t"
        "addl b, %eax\n\t"
        "movl %eax, c");
    printf("c = %d \n", c);
    return 0;
}
