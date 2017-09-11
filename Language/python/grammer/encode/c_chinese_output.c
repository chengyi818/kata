#include <stdio.h>
#include <unistd.h>

int main(void) {
    char* a = "中\n";
    char* b = "a\n";
    printf("%s", a);
    printf("%s", b);
    write(1, "\344\270\255\n", 4);
    write(1, "\xe4\xb8\xad\n", 4);
}
