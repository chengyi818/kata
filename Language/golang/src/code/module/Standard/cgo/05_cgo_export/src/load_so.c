/*
 * File Name: load_so.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 12 Apr 2019 02:03:37 PM CST
 */

#include "load_so.h"
#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>

int do_test_so_func(int a,int b)
{
    void* handle;
    typedef int (*FPTR)(void*, int,int);
    int result = 0;

    handle = dlopen("../lib/test_so.so", RTLD_LAZY);
    FPTR fptr = (FPTR)dlsym(handle, "test_so_func");


    // success
    result = (*fptr)((void*)Hello, a, b);

    // fail
    int pid = fork();
    if(pid == 0) {
        result = (*fptr)((void*)Hello, a, b);
    } else {
        int exitCode;
        waitpid(pid, &exitCode, 0);
    }

    // fail
    /* int pipe_fd[2]; */
    /* if(pipe(pipe_fd) != -1) { */
    /*     int pid = fork(); */
    /*     if(pid == 0) { */
    /*         ssize_t i; */
    /*         int ret = (*fptr)((void*)Hello, a, b); */
    /*         i = write(pipe_fd[1], &ret, sizeof(int)); */
    /*         close(pipe_fd[1]); */
    /*         _exit(0); */
    /*     } else { */
    /*         int exitCode; */
    /*         ssize_t i; */
    /*         close(pipe_fd[1]); */
    /*         i = read(pipe_fd[0], &result, sizeof(int)); */
    /*         close(pipe_fd[0]); */

    /*         if(waitpid(pid, &exitCode, 0) != pid) { */
    /*             result = 10000; */
    /*         } */
    /*     } */
    /* } */

    return result;
}
