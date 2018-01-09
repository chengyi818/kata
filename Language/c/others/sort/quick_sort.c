/*
 * File Name: quick_sort.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 09 Jan 2018 09:36:54 AM CST
 */
#include <stdio.h>

void show_array(int *s, unsigned long size) {
    for(unsigned long i=0; i<size; i++) {
        printf("%d ", s[i]);
    }
    printf("\n");
}

void quick_sort(int *s, unsigned long start, unsigned long end) {
    if(start>=end)
        return;

    unsigned long i = start;
    unsigned long j = end;

    while(i != j) {
        while(s[j] >= s[start] && j>i) {
            j--;
        }
        while(s[i] <= s[start] && i<j) {
            i++;
        }
        s[i] = s[i] ^ s[j];
        s[j] = s[i] ^ s[j];
        s[i] = s[i] ^ s[j];
        show_array(s, end-start+1);
    }

    s[start] = s[start] ^ s[i];
    s[i] = s[start] ^ s[i];
    s[start] = s[start] ^ s[i];
    show_array(s, end-start+1);

    /* quick_sort(s, start, i-1); */
    /* quick_sort(s, i+1, end); */
}


int main(void) {
    int array[10] = {4, 2, 3, 1, 5, 6, 8, 9, 0, 7};

    // 数组长度
    /* printf("%lu\n", sizeof(array)/sizeof(array[0])); */
    unsigned long size = sizeof(array)/sizeof(array[0]);

    show_array(array, size);
    quick_sort(array, 0, size-1);
    show_array(array, size);

    return 0;
}
