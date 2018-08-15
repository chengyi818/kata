/*
 * File Name: bubble_sort.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 05 Jan 2018 09:24:10 AM CST
 */
#include <stdio.h>

void show_array(int *s, unsigned long size) {
    for(unsigned long i=0; i<size; i++) {
        printf("%d ", s[i]);
    }
    printf("\n");
}

int bubble_sort(int *s, unsigned long size) {
    show_array(s, size);
    for(unsigned long i=0; i<size-1; i++) {
        for(unsigned long j=i+1; j<size; j++) {
            if(s[i] > s[j]) {
                s[i] = s[i]^s[j];
                s[j] = s[i]^s[j];
                s[i] = s[i]^s[j];
            }
        }
    }

    return 0;
}


int main(void) {
    int array[10] = {4, 2, 3, 1, 5, 6, 8, 9, 0, 7};

    // 数组长度
    /* printf("%lu\n", sizeof(array)/sizeof(array[0])); */
    unsigned long size = sizeof(array)/sizeof(array[0]);

    bubble_sort(array, size);

    show_array(array, size);

    return 0;
}
