#include <stdio.h>

int main()
{
    int c = 0;
    int nb = 0;
    int nt = 0;
    int nl = 0;
    while((c = getchar()) != EOF)
    {
        if(c == ' ')
            nb++;
        else if(c == '\t')
            nt++;
        else if(c == '\n')
            nl++;
    }

    printf("new blank:%d\t,new tab:%d\t,new line:%d\t", nb, nt, nl);
    return 0;
}
