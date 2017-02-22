#include <stdio.h>
#include <string.h>

int function(int arg)
{
    return arg;
}

int main(void)
{
    int i = 10;
    int j;
    j = function(i);
    printf("%d\n",j);
    return 0;
}
