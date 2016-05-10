/*=============================================================================
#     FileName: integer_overflow_check.c
#         Desc: http://coolshell.cn/articles/11466.html
#       Author: ChengYi
#        Email: chengyi@antiy.cn
#     HomePage: http://www.antiy.com/
#      Created: 2016-05-10 14:27:35
#      Version: 0.0.1
#   LastChange: 2016-05-10 14:27:35
#      History:
#               0.0.1 | ChengYi | init
=============================================================================*/
#include <unistd.h>
#include <cstdint>
#include <limits.h>

/*错误*/
void foo_error(int m, int n)
{
    size_t s = m + n;
    if ( m>0 && n>0 && (SIZE_MAX - m < n) ){
        //error handling...
    }
}

/*正确*/
void foo_correct(int m, int n)
{
    size_t s = 0;
    if ( m>0 && n>0 && ( UINT_MAX - m < n ) ){
        //error handling...
        return;
    }
    s = (size_t)m + (size_t)n;
}

/*二分取中搜索算法中的溢出*/
int binary_search(int a[], int len, int key)
{
    int low = 0;
    int high = len - 1;

    while ( low<=high ) {
        int mid = (low + high)/2;
        if (a[mid] == key) {
            return mid;
        }
        if (key < a[mid]) {
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }
    return -1;
}

/*上溢出和下溢出的检查*/
void f(signed int si_a, signed int si_b) {
    signed int sum;
    if (((si_b > 0) && (si_a > (INT_MAX - si_b))) ||
        ((si_b < 0) && (si_a < (INT_MIN - si_b)))) {
        /* Handle error */
        return;
    }
    sum = si_a + si_b;
}
