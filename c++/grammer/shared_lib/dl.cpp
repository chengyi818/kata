/*
 * File Name: dl.cpp
 * Author: ChengYi
 * Mail: chengyi@antiy.cn
 * Created Time: Fri 29 Jul 2016 02:34:02 PM CST
 */

#define protected public
#define private public
#include "a.h"
#include <dlfcn.h>
#include <cstdlib>

int main(void) {
    typedef void (*A_constructor_ptr)(A*);
    typedef void (*pri_set_ptr)(A*, int);

    void* handle = dlopen("./liba.so", RTLD_LAZY);
    if(handle == NULL) {
        std::cout << "dlopen error" <<std::endl;
        return 1;
    }
    A_constructor_ptr A_constructor = (A_constructor_ptr) dlsym(handle, "_ZN1AC2Ev");
    if(A_constructor == NULL) {
        std::cout << "dlsym error" <<std::endl;
        return 1;
    }

    pri_set_ptr pri_set = (pri_set_ptr) dlsym(handle, "_ZN1A7pri_setEi");
    if(pri_set == NULL) {
        std::cout << "dlsym error" <<std::endl;
        return 1;
    }

    A* Ap = (A*) malloc(sizeof(class A));
    A_constructor(Ap);
    std::cout << "Ap->mdata:" << Ap->mdata <<std::endl;

    pri_set(Ap, 4);
    std::cout << "Ap->mdata:" << Ap->mdata <<std::endl;

    return 0;
}


