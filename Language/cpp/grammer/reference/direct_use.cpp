/*
 * File Name: r1.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Tue 04 Jul 2017 05:20:15 PM CST
 */
#include <iostream>
#include "point.h"

int main()
{
    getPointer()->printPoint();
    getReference().printPoint();

    return 0;
}
