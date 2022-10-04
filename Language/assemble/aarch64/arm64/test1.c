#include <stdio.h>

int main()
{
    asm volatile ("nop");
    printf("hello\n");
    asm volatile ("nop\n\tnop\n\t");

    return 0;
}
