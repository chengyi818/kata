#include <stdio.h>

int main(void)
{
    int c;
    int out = -1;
    while((c = getchar()) != EOF)
    {
        if(c == ' ' || c == '\t' || c == '\n')
        {
            out = 1;
            continue;
        }
        if(out == 1)
        {
            printf("\n");
            out = -1;
        }
        putchar(c);
    }

    return 0;
}
