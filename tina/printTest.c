#include <string.h>
#include <stdio.h>
#include <stdlib.h>



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct hash_node {
    int id;            /* we'll use this field as the key */
    int index;
    UT_hash_handle hh; /* makes this structure hashable */
} hash_node;

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int *two_nums = (int *)malloc(sizeof(int)*2);
    hash_node *hash_table = NULL, *hash_item1 = NULL, *hash_item2 = NULL;
    for (int i = 0; i < numsSize; i++) {
        // 查找哈希表中是否存在满足和为target的另一个值,若存在直接返回
        int other_id = target - *(nums+i);
        HASH_FIND_INT(hash_table, &other_id, hash_item1);
        if (hash_item1) {
            two_nums[0] = hash_item1->index;
            two_nums[1] = i;
            *returnSize = 2;
            return two_nums;
        }
        // 将本次遍历的值放入哈希表,value为数组下标,key为对应数值
        hash_item2 = (hash_node *)malloc(sizeof(hash_node));
        hash_item2->id = *(nums+i);
        hash_item2->index = i;
        HASH_ADD_INT(hash_table, id, hash_item2);
    }
    return two_nums;
}



/*ToDo: 
 *1. for循环scanf读取多个以空格间隔的字符有些问题;
 *2. C中的以某个字符为分割的字符串切割处理
 */
int main(void) {
    int i,j,k;

    char a,b,c;

    char strA[100];
    char strB[100];
    char strC[100];
    char* string = strC;

    int array[100];
    char charArray[100];
    int index = 0;

    int **intMatrix;
    char **charMatrix;
    int m,n;

    char strArray[100][100];
    char* stringArray[10];  //可最多存放10个字符串

    /*1. 读入3个整数/字符,多个整数以空白字符(空格 回车符 tab键)隔开; scanf遇到这类空白字符,会连续读取输入流中空白字符,但不会存储*/
    #if 0
    printf("1.1 请输入3个非负整数(以空格 回车符 tab键隔开):如1 2 3\n");
    scanf("%d%d%d",&i,&j,&k);
    printf("i=%d, j=%d, k=%d. \n",i,j,k);
    */

    printf("1.2 请输入3个非负整数/字符(以空格 回车符 tab键隔开):如123a6\n");
    scanf("%d%c%d",&i,&a,&j);
    printf("i=%d, a=%c, j=%d. \n",i,a,j);
    printf("i=%d, a=%d, j=%d. \n",i,a,j);
    

    printf("1.3 请输入3个非负整数(以空格 回车符 tab键隔开):如1 2 3\n");
    scanf("%d %d %d",&i,&j,&k);
    printf("i=%d, j=%d, k=%d. \n",i,j,k);

    /*2. 读入3个字符,多个字符以空格 回车符 tab键隔开*/
    /*Note:当多个scanf连续执行,并且有字符注入混合时,需要清空缓冲区中的回车符*/
    printf("2.1 请输入3个字符(以空格 回车符 tab键隔开):如1 2 3,a b c\n");
    scanf(" %c %c %c",&a,&b,&c);    //第一个空白字符接收缓冲区残留的回车符
    printf("a=%c, b=%c, c=%c. \n",a,b,c);

    /*Note:当多个getchar连续执行,是从缓冲区中读入一个字符,包含回车符,可以使用getchar过滤回车或者直接连续输入;
     *如果有多个字符残留,直接使用fflush(stdin)清空所有字符,直接从键盘获取输入;*/
    printf("2.2 请输入3个字符(连续输入):如123,abc\n");
    getchar();  //清除接收缓冲区残留的回车符
    a = getchar();
    b = getchar();
    c = getchar()

    printf("a=%c, b=%c, c=%c. \n",a,b,c);

    /*3. 读入2个字符串*/
    /*Note: gets与getchar不同,会将缓冲区最后的回车符取出来并丢弃,不会有残留*/
    printf("3.1 请输入字符串(可以带空格):如123,abc,Yi Ting\n");
    getchar();  //清除接收缓冲区残留的回车符
    gets(strA); //gets接收输入的整个字符串直到遇到换行为止
    printf("gets string:%s. \n",strA);
    

    printf("3.2 请输入2个字符串(单个字符串不带空格,中间以空格 回车符 tab键隔开):如Yi Ting,FatCheng TinaZhu\n");
    scanf("%s %s",string,strA); //scanf遇到空格则会认为字符串结束
    printf("scanf string1:%s, string2:%s \n",string,strA);

    printf("3.3 字符串与单个字符混合:\n");
    printf("请输入2个字符串(单个字符串不带空格,中间以空格 回车符 tab键隔开):如Yi Ting,FatCheng TinaZhu\n");
    scanf("%s%s",string,strA); //scanf遇到空格则会认为字符串结束
    printf("scanf string1:%s, string2:%s \n",string,strA);
    printf("请输入单个字符:如a\n");
    getchar();  //清除接收缓冲区残留的回车符
    a = getchar();
    printf("a=%c\n",a);
    printf("请再次输入2个字符串(单个字符串不带空格,中间以空格 回车符 tab键隔开):如Yi Ting,FatCheng TinaZhu\n");
    scanf("%s %s",string,strA); //scanf遇到空格则会认为字符串结束
    printf("scanf string1:%s, string2:%s \n",string,strA);
    


    /*4. 读入多个整数/字符,多个整数/字符以空白字符(空格 回车符 tab键)隔开*/
    printf("4.1 请输入一维数组,已知个数(数量较多,使用循环输入)\n");
    printf("请输入整数个数:如3\n");
    scanf("%d",&i);
    printf("请请输入多个非负整数(以空格 回车符 tab键隔开):如1 2 3 4......\n");
    while(index < i){
        scanf("%d",&array[index]);
        printf("array[%d]=%d. \n",index,array[index]);
        index++;
    }
      
    
    printf("4.2 请输入一维整数数组,未知个数(中间以空格隔开):如1 2 3 4 5......\n");
    index = 0;
    //while(scanf("%d",&array[index]) != EOF){    
        //scanf返回值为赋值的参数个数,读取结束时也就是参数为空,则为-1即EOF,是否用于文件输入较好
    do{
        scanf("%d",&array[index]);
        printf("array[%d]=%d. \n",index,array[index]);
        index++;
    }while(getchar() != '\n');   //若输入回车代表输入结束

    printf("4.3 请输入一维字符数组,未知个数(中间以空格隔开):如a b c d e......\n");
    index = 0;
    do{
        //scanf("%c",&charArray[index]);
        charArray[index] = getchar();
        printf("charArray[%d]=%c. \n",index,charArray[index]);
        index++;
    }while(getchar() != '\n')  printf("请请输入多个非负整数(以空格 回车符 tab键隔开):如1 2 3 4......\n");
    while(index < i){
        scanf("%d",&array[index]);
        printf("array[%d]=%d. \n",index,array[index]);
        index++;
    };   //若输入回车代表输入结束
      printf("请请输入多个非负整数(以空格 回车符 tab键隔开):如1 2 3 4......\n");
    while(index < i){
        scanf("%d",&array[index]);
        printf("array[%d]=%d. \n",index,array[index]);
        index++;
    }
    printf("请请输入多个非负整数(以空格 回车符 tab键隔开):如1 2 3 4......\n");
    while(index < i){
        scanf("%d",&array[index]);
        printf("array[%d]=%d. \n",index,array[index]);
        index++;
    }
    /*5. 读入多行多列整数/字  printf("请请输入多个非负整数(以空格 回车符 tab键隔开):如1 2 3 4......\n");
    while(index < i){
        scanf("%d",&array[index]);
        printf("array[%d]=%d. \n",index,array[index]);
        index++;
    }符,多个整数/字符以空白字符(空格 回车符 tab键)隔开*/
    printf("5.1 请输入二维整数数组,已知个数(中间以空格隔开)\n");
    printf("请输入矩阵行数和列数:如3 4\n");
    scanf("%d%d",&m,&n);
    intMatrix = (int**)malloc(m*sizeof(int*));
    for(i = 0; i < m; i++){
        intMatrix[i] = (int*)malloc(n*sizeof(int));
        for(j = 0; j < n; j++){
            scanf("%d",&intMatrix[i][j]);
            //printf("intMatrix[%d][%d]=%d  ",i,j,intMatrix[i][j]);
        }
        //printf("\n");
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d  ",intMatrix[i][j]);
        }
        printf("\n");
    }
    

    printf("5.2 请输入二维字符数组,已知个数(中间以空格隔开)\n");
    printf("请输入矩阵行数和列数:如3 4\n");
    scanf("%d%d",&m,&n);
    getchar();  //清除接收缓冲区残留的回车符
    charMatrix = (char**)malloc(m*sizeof(char*));
    for(i = 0; i < m; i++){
        charMatrix[i] = (char*)malloc(n*sizeof(char));
        for(j = 0; j < n; j++){
            scanf("%c",&charMatrix[i][j]);          
            //printf("charMatrix[%d][%d]=%c  ",i,j,charMatrix[i][j]);
        }
        getchar();  //清除接收缓冲区残留的回车符
        //printf("\n");
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%c ",charMatrix[i][j]);
        }
        printf("\n");
    }
    #endif

    /*6. 读入多个字符串,多个字符串以空白字符(空格 回车符 tab键)隔开,个数未知*/
    printf("6.1 请输入多个字符串,个数未知(中间以空格隔开):如we are ok......\n");
    index = 0;
    do{
        scanf("%s",strArray[index]);
        printf("strArray[%d]=%s. \n",index,strArray[index]);
        index++;
    }while(getchar() != '\n');   //若输入回车代表输入结束

    printf("6.2 请输入多个字符串,个数已知(中间以空格隔开)\n");
    printf("请输入字符串个数:如4\n");
    scanf("%d",&m);
    index = 0;
    printf("请请输入多个字符串(以空格 回车符 tab键隔开):如we are ok\n");
    while(index < m){
        scanf("%s",strArray[index]);
        printf("strArray[%d]=%s. \n",index,strArray[index]);
        index++;
    }

    printf("6.3 请输入多个字符串,个数未知(中间以空格隔开)\n");
    gets(charArray); 
    index = 0;
    printf("请请输入多个字符串(以空格 回车符 tab键隔开):如we are ok\n");
    while(index < m){
        scanf("%s",strArray[index]);
        printf("strArray[%d]=%s. \n",index,strArray[index]);
        index++;
    }


    return 0;
}
