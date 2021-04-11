#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_ROW 1000

bool IsPalindrome(char* s, int start, int end) {
    //printf("IsPalindrome, start: %d, end: %d\n", start, end);
    bool ret = false;
    while(start<=end) {
        if(s[start] != s[end]) {
             goto DONE;
        }
        start++;
        end--;
    }
    ret = true;

DONE:
    //printf("IsPalindrome, ret: %d\n", ret);
    return ret;
}

void SaveResult(char* s, int* stack, int stackIndex, char*** ret, int* returnSize, int** returnColumnSizes) {
    (*returnColumnSizes)[*returnSize] = stackIndex;
    ret[*returnSize] = (char**)malloc(sizeof(char*)*stackIndex);
    char* tmpChar = NULL;
    int tmpSize = 0;
    int wordStart = 0;

    for(int i=0; i<stackIndex; i++) {
        tmpSize = stack[i]+1;
        tmpChar = (char*)malloc(sizeof(char)*tmpSize);
        memset(tmpChar, 0, tmpSize);
        strncpy(tmpChar, &s[wordStart], tmpSize-1);
        wordStart += stack[i];

        ret[*returnSize][i] = tmpChar;
    }

    //printf("*returnSize: %d\n", *returnSize);
    //printf("(*returnColumnSize)[*returnSize]: %d\n", (*returnColumnSizes)[*returnSize]);
    (*returnSize)++;
    //printf("----------------\n");
}


void Backtrace(char* s, int start, int len,
               char*** ret, int* returnSize, int** returnColumnSizes,
               int* stack, int stackIndex) {
    //printf("Backtrace, start: %d\n", start);
    for(int i=start; i<len; i++) {
        if(IsPalindrome(s, start, i)) {
            // save current len to stack
            stack[stackIndex++] = i-start+1;

            // handle last string
            if(i == (len-1)) {
                SaveResult(s, stack, stackIndex, ret, returnSize, returnColumnSizes);
                return;
            }

            Backtrace(s, i+1, len, ret, returnSize, returnColumnSizes, stack, stackIndex);
            stackIndex--;
        }
    }
}


char *** partition(char * s, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    int len = strlen(s);
    int stackIndex = 0;

    int stack[MAX_ROW] = {0};
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX_ROW);
    char*** ret = (char***)malloc(sizeof(char**) * MAX_ROW);

    Backtrace(s, 0, len, ret, returnSize, returnColumnSizes, stack, stackIndex);

    return ret;
}

int main() {
    char* s= "xxxxxxxxxxx";
    int returnSize;
    int* returnColumnSizes = NULL;

    char*** ret = partition(s, &returnSize, &returnColumnSizes);

}
