/*
 * File Name: main.cpp
 * Author: ChengYi
 * Mail: chengyi@antiy.cn
 * Created Time: Fri 29 Jul 2016 11:34:07 AM CST
 */

#define protected public
#define private public
#include "a.h"

int main(void) {
    A* Ap = new A;

    Ap->pub_get();
    Ap->pub_set(4);
    Ap->pub_get();
    Ap->pro_set(5);
    Ap->pro_get();
    Ap->pri_set(6);
    Ap->pri_get();

    delete Ap;

    return 0;
}
