/*
 * File Name: a.h
 * Author: ChengYi
 * Mail: chengyi@antiy.cn
 * Created Time: Fri 29 Jul 2016 11:27:06 AM CST
 */

#ifndef __A_H__
#define __A_H__
#include <iostream>

class A{
public:
    A();
    ~A();
    void pub_set(int value);
    void pub_get();
protected:
    void pro_set(int value);
    void pro_get();
private:
    void pri_set(int value);
    void pri_get();
    int mdata;
};

#endif /* __A_H__ */
