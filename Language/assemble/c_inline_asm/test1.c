#include <stdio.h>

int main()
{
    asm ("nop");
    printf("hello\n");
    asm ("nop\n\tnop\n\t"
	 "nop");
    return 0;
}
