#include <stdio.h>

int a = 1;
int b = 2;
int c;

int main()
{
    asm volatile (
        "adrp x2, a\n\t"
        "add x2, x2, :lo12:a\n\t"
        "ldr x0, [x2]\n\t"

        "adrp x2, b\n\t"
        "add x2, x2, :lo12:b\n\t"
        "ldr x1, [x2]\n\t"

        "add x0, x0, x1\n"

        "adrp x2, c\n\t"
        "add x2, x2, :lo12:c\n\t"

        "str x0, [x2]\n\t");
    printf("c = %d\n", c);
    return 0;
}
