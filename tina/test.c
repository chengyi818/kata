#include <string.h>
#include <stdio.h>

int numJewelsInStones(char * J, char * S){
    char *tempS = S;
    int JewelsNum = 0;
    unsigned long indexJ;

    for(indexJ = 0; indexJ < strlen(J); indexJ++ ){
        while( strchr(tempS, J[indexJ]) ){
            JewelsNum++;
            tempS = strchr(tempS, J[indexJ]);
            tempS++;
        }
    }

    return JewelsNum;
}

int main(void) {
    char* J = "aA";
    char* S = "aAAbbbb";

    int ret = numJewelsInStones(J, S);
    printf("%d\n", ret);
    return 0;
}
