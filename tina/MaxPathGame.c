#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE(a,b) ((a)>=(b)?(a):(b))

int maxSum(int** matrix, int n, int i, int j){
    if(i < 0 || j > n-1){
        return 0;
    }
    return matrix[i][j] + MAX_VALUE(maxSum(matrix,n,i-1,j),maxSum(matrix,n,i,j+1));
}

int main(void) {
    int m,n,i,j;
    int** intMatrix;
    int maxSumValue = 0;

    printf("请输入矩阵行数和列数,以空格隔开:\n");
    scanf("%d%d",&m,&n);

    printf("输入矩阵数据:\n");
    intMatrix = (int** )malloc(m*sizeof(int*));
    for(i = 0; i < m; i++){
        intMatrix[i] = (int*)malloc(n*sizeof(int));
        for(j = 0; j < n; j++){        
            scanf("%d",&intMatrix[i][j]);
        }
    }

    printf("矩阵数据为:\n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d ",intMatrix[i][j]);
        }
        printf("\n");
    }

    maxSumValue = maxSum(intMatrix,n,m-1,0);
    printf("maxSumValue = %d\n",maxSumValue);

    return 0;
}
