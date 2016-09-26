#include <stdio.h>

void if1(int n) {
    if(n < 10) {
        printf("the number less than 10\n");
    } else {
        printf("the number greater than or equal to 10\n");
    }
}

void if2(int n) {
    if(n < 16) {
        printf("n < 16\n");
    } else if(n < 30) {
        printf("n < 30\n");
    } else if(n < 45) {
        printf("n < 45\n");
    } else {
        printf("n > 45\n");
    }
}

int main(void)
{
    if1(5);
    if2(35);
    return 0;
}
