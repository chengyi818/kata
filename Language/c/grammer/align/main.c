#include <stdio.h>

#pragma pack(4)
struct A {
    struct {
        unsigned long b;
        int c;
    } B;
    int d;
};


int main() {
    printf("sizeof A: %lu\n", sizeof(struct A));
    return 0;
}
