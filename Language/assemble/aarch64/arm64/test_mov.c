#include <stdio.h>

int a = 1;
int b = 2;
int c;

int main()
{
    unsigned long a = 0;
    unsigned long b = 0;
    // wrong
    /*asm volatile ("mov x0, 0x1abcd\n\t");*/

    asm volatile (
        "string1: \n\t"
        ".string 'Boot'"
        "ldr  %1, string1\n"
        "ldr %2, =string1\n"
        :"=r"(a), "=r"(b)
    );
    printf("c = %d\n", c);
    return 0;
}
