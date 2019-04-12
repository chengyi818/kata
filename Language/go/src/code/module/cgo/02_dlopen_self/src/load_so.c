/*
 * File Name: load_so.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 12 Apr 2019 02:03:37 PM CST
 */

#include "load_so.h"
#include <dlfcn.h>

int do_test_so_func(int a,int b)
{
    void* handle;
    typedef int (*FPTR)(int,int);

    handle = dlopen("../lib/test_so.so", 1);
    FPTR fptr = (FPTR)dlsym(handle, "test_so_func");

    int result = (*fptr)(a,b);
    return result;
}
