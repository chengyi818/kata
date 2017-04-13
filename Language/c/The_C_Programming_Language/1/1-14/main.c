#include <stdio.h>
#include <stdlib.h>

#define OUT 1
#define IN 0

typedef struct word_data {
    int index;
    int length;
    struct word_data *pNext;
} WORD_DATA;

int main(void)
{
    int c;
    int state = OUT;

    WORD_DATA *pHead = (WORD_DATA *)malloc(sizeof(WORD_DATA));
    pHead->length = -1;
    pHead->index = 0;
    pHead->pNext = NULL;
    WORD_DATA *pTail = pHead;
    WORD_DATA *pTemp = pHead;

    while((c = getchar()) != EOF)
    {
        if( (c != '\t') && (c != '\n') && (c != ' ') && (state == OUT))
        {
            pTemp = (WORD_DATA *)malloc(sizeof(WORD_DATA));
            pTemp->index = pTail->index + 1;
            pTemp->length = 1;
            pTemp->pNext = NULL;
            pTail->pNext = pTemp;
            pTail = pTemp;
            state = IN;
        }
        else if( (c != '\t') && (c != '\n') && (c != ' ') && (state == IN) )
        {
             pTail->length++;
        }
        else if( (c == '\t') ||  (c == '\n') || (c == ' '))
        {
            state = OUT;
        }
    }

    /*打印*/
    for(pTemp = pHead->pNext; pTemp->pNext != NULL; pTemp = pTemp->pNext)
    {
        printf("Index:%2d\t Length:%2d :", pTemp->index, pTemp->length);
        for(c = pTemp->length; c>0; c--)
            printf("*");
        printf("\n");
    }


    for(pTemp = pHead->pNext; pHead!=NULL; pHead=pTemp,pTemp = pHead->pNext)
        free(pHead);

    return 0;
}
