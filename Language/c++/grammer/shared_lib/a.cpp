/*
 * File Name: a.cpp
 * Author: ChengYi
 * Mail: chengyi@antiy.cn
 * Created Time: Fri 29 Jul 2016 11:26:57 AM CST
 */

#include "a.h"
#include <iostream>


A::A() {
    std::cout << "A的构造函数被调用" << std::endl;
    mdata = 0;
}

A::~A() {
    std::cout << "A的析构函数被调用" << std::endl;
}

void A::pub_set(int value) {
    mdata = value;
}

void A::pub_get() {
    std::cout << "mdata:" << mdata << std::endl;
}

void A::pro_set(int value) {
    mdata = value;
}

void A::pro_get() {
    std::cout << "mdata:" << mdata << std::endl;
}


void A::pri_set(int value) {
    mdata = value;
}

void A::pri_get() {
    std::cout << "mdata:" << mdata << std::endl;
}
