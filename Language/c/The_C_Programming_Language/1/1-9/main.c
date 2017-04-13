#include <stdio.h>


int main(void)
{
    int c;
    int lastc = -1;
    while((c=getchar()) != EOF)
    {
        if(c != ' ' || lastc != ' ')
            putchar(c);
        lastc = c;
    }
    return 0;
}
