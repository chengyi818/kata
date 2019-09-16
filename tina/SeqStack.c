#include <string.h>
#include <stdio.h>

#define MAX_STACK_SIZE  20000

typedef struct{
    int* data;
    int top;
}SqStack;

bool InitStack(SqStack s){
    s.data = (int* )malloc(sizeof(int) * MAX_STACK_SIZE);
    if(s.data == NULL){
        return 0;
    }
    s.top = -1;
    return 1;
}

bool Push(SqStack s, int e){
    if(s.top == MAX_STACK_SIZE - 1){
        return 0;
    }
    s.data[++s.top] = e;
    return 1;
}

bool Pop(SqStack s, int *e){
    if(s.top == -1){
        return 0;
    }
    *e = s.data[s.top--];
    return 1;
}

bool StackEmpty(SqStack s){
    if(s.top == -1){
        return 1;
    }
    return 0;
}


int main(void) {
    char* J = "aA";
    char* S = "aAAbbbb";

    int ret = numJewelsInStones(J, S);
    printf("%d\n", ret);
    return 0;
}
