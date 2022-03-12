#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *restrict pInt = (int*)malloc(4);
    int *pNewInt = pInt;
    *pInt = 3;
    *pNewInt = 4;
    printf("%d\n", *pInt);
    printf("%d\n", *pNewInt);
    return 0;
}
