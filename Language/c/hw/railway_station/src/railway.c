/*
 * File Name: main.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 22 Mar 2019 09:55:37 AM CST
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "railway.h"


/* int main() { */
/*     char* pOutSeq = "53241"; */

/*     int ret = JudgeTrainSequence(5, pOutSeq); */
/*     printf("ret: %d\n", ret); */

/*     return 0; */
/* } */


char TRAIN_NUM[] = "0123456789";
int JudgeTrainSequence(int maxNum, char* pOutSeq) {
    // TODO: maybe need some check for input, such as maxNum
    if(maxNum < 1 || maxNum >9) {
        return 0;
    }
    if(strlen(pOutSeq) != (unsigned int)maxNum) {
        return 0;
    }

    // the train num we currently search
    char currentTarget = TRAIN_NUM[maxNum];
    // the train left on output sequence
    int outNum = maxNum;
    // simulate stack
    char stack[10];
    int top = 0;

    /**
     * 1. pop outSeq and push pop value to stack,until currentTarget is on top of outSeq.
     * 2. pop outSeq
     * 3. if currentTarget = 1, return 1, else currentTarget - 1
     * 4. if currentTarget in in outSeq, jump to STEP 1.
     * 5. if currentTarget in stack, it should on the stack top, pop and jump to STEP 3.
     * 6. if currentTarget in stack and not on the top, return 0.
     */
STEP1:
    while(pOutSeq[outNum-1] != currentTarget) {
        stack[top++] = pOutSeq[outNum-1];
        outNum--;

        if(outNum<1) {
            // 此时中间一定有非法字符
            return 0;
        }
    }

/* STEP2: */
    outNum--;

STEP3:
    if(currentTarget == '1') {
        return 1;
    } else {
        currentTarget -= 1;
    }

/* STEP4: */
    for(int i = 0; i < outNum; i++) {
        if(pOutSeq[i] == currentTarget) {
            goto STEP1;
        }
    }

/* STEP5: */
    if(stack[top-1] == currentTarget) {
        top--;
        goto STEP3;
    }

/* STEP6: */
    return 0;
}
