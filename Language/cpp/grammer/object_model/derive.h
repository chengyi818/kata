#include <iostream>
#include "base.h"

#ifndef DERIVE_H
#define DERIVE_H
using namespace std;

class Derive : public Base {
  public:
    Derive(int d): Base(1000), DeriveI(d) {
        cout << "Drive::constructor()" << endl;
    };
    //overwrite父类虚函数
    virtual void print(void) {
        cout << "Drive::print()" << endl;
    }
    // Derive声明的新的虚函数
    virtual void Drive_print() {
        cout << "Drive::Drive_print()" << endl;
    }
    virtual ~Derive() {
        cout << "Drive::deconstructor()" << endl;
    }
  private:
    int DeriveI;
};

#endif
