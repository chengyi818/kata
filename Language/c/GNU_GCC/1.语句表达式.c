/*=============================================================================
#     FileName: 1.语句表达式.c
#         Desc:
#       Author: ChengYi
#        Email: chengyi818@foxmail.com
#     HomePage:
#      Created: 2018-08-15 11:46:38
#      Version: 0.0.1
#   LastChange: 2018-08-15 11:46:38
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/
#include <stdio.h>

#define maxint(a, b) \
           ((a)>(b) ? (a) : (b))

#define maxint2(a, b) \
    ({ \
int _a = (a); \
int _b = (b); \
_a > _b ? _a : _b; \
}) \


int main() {
    int a = 3;
    int b = 4;
    printf("%d\n", maxint(++a, ++b));

    a = 3;
    b = 4;
    printf("%d\n", maxint2(++a, ++b));

    return 0;
}
