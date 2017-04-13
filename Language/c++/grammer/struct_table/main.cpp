#include <stdio.h>

typedef struct node
{
    int a;
    char b;
}NODE;

int main(void)
{
    NODE * pNODE;
    pNODE = new NODE[4];
    printf("pNODE address is %p\n", pNODE);
    printf("pNODE[3] address is %p\n", &pNODE[3]);
    printf("pNODE+3 address is %p\n", pNODE + 3);

    return 0;
}
