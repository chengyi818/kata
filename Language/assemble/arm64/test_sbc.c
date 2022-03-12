#include <stdio.h>

int main()
{
    unsigned long idx = 1;
    unsigned long size = 1;
    unsigned long mask = 1;
    asm volatile (
        "cmp %1, %2\n"
        "sbc %0, xzr, xzr\n"
        :"=r"(mask)
        :"r"(idx), "r"(size)
    );
    printf("mask: %lu\n", mask);
    return 0;
}
