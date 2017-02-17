/* @filename:example_2_2.c */

/*PS:函数get_str_1()返回Stack段数据，编译时会报错。
 * Heap中的数据，如果不用了，应该尽早释放free()。*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_str_1()
{
    char str[] = "hello world";
    return str;
}

char *get_str_2()
{
    char *str = "hello world";
    return str;
}

char *get_str_3()
{
    char tmp[] = "hello world";
    char *str;

    str = (char *)malloc(12 * sizeof(char));
    memcpy(str, tmp, 12);

    return str;
}

int main(int argc, char *argv[])
{
    char *str_1 = get_str_1();  //出错了，Stack段中的数据在函数退出时就销毁了
    char *str_2 = get_str_2();  //正确，指向Text段中的字符直接量，退出程序后才会回收
    char *str_3 = get_str_3();  //正确，指向Heap段中的数据，还没free()

    printf("%s\n", str_1);
    printf("%s\n", str_2);
    printf("%s\n", str_3);

    if (str_3 != NULL)
    {
        free(str_3);
        str_3 = NULL;
    }

    return 0;
}
