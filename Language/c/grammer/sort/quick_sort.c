/*
 * File Name: quick_sort.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 09 Jan 2018 09:36:54 AM CST
 */
#include <stdio.h>
static int size;

void show_array(int *s, int size) {
    for(int i=0; i<size; i++) {
        printf("%d ", s[i]);
    }
    printf("\n");
    printf("\n");
}

void quick_sort(int *s, int start, int end) {
    if(start >= end)
        return;

    int i = start;
    int j = end;

    printf("put %d in right position\n", s[start]);
    while(i != j) {
        while(s[j] >= s[start] && j>i) {
            j--;
        }
        while(s[i] <= s[start] && i<j) {
            i++;
        }
        if(i != j) {
            printf("swap %d %d\n", s[i], s[j]);
            s[i] = s[i] ^ s[j];
            s[j] = s[i] ^ s[j];
            s[i] = s[i] ^ s[j];
            show_array(s, size);
        }
    }

    if(start != i) {
        printf("swap %d %d\n", s[start], s[i]);
        s[start] = s[start] ^ s[i];
        s[i] = s[start] ^ s[i];
        s[start] = s[start] ^ s[i];
        show_array(s, size);
    }

    quick_sort(s, start, i-1);
    quick_sort(s, i+1, end);
}


int main(void) {
    int array[10] = {4, 2, 3, 1, 5, 6, 8, 9, 0, 7};
    /* int array[5] = {4, 3, 2, 1, 5}; */

    // 数组长度
    size = (int)sizeof(array)/sizeof(array[0]);

    printf("show array at first\n");
    show_array(array, size);

    quick_sort(array, 0, size-1);

    printf("show array at last\n");
    show_array(array, size);

    return 0;
}
