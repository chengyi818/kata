/*
 * File Name: dlopen.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 04 Jul 2017 06:32:57 PM CST
 */
#include "point.h"
#include <dlfcn.h>
#include <stdio.h>

typedef class Point* (*getPointer_p)();
typedef class Point& (*getReference_p)();

int main() {
    void* handle = dlopen("./libpoint.so", RTLD_LAZY);

    getPointer_p getPointer_f = (getPointer_p)dlsym(handle, "_Z10getPointerv");
    getPointer_f();
    // class Point* pPoint = getPointer_f();
    // pPoint->printPoint();
    // pPoint->printAddr();

    printf("-------------\n");
    getReference_p getReference_f = (getReference_p)dlsym(handle, "_Z12getReferencev");
    getReference_f();
    // class Point& rPoint = getReference_f();
    // rPoint.printPoint();
    // rPoint.printAddr();

    // printf("-------------\n");
    // class Point mPoint;
    // mPoint.printPoint();
    // mPoint.printAddr();

    // printf("-------------\n");
    // mPoint = rPoint;
    // mPoint.printPoint();
    // mPoint.printAddr();

    return 0;
}
