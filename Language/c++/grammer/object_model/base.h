#include <iostream>

#ifndef BASE_H
#define BASE_H
using namespace std;

class Base {
  public:
    Base(int i=0) : baseI(i) {
        cout << "base constructor" << endl;
    };
    int getI() {
        cout << "base getI: "<<baseI<< endl;
        return baseI;
    }
    static void countI() {
        cout << "base countI" << endl;
    };
    virtual void print(void) {
        cout << "Base::print()" << endl;
    }
    virtual ~Base() {
        cout << "base deconstructor" << endl;
    }
  private:
    int baseI;
    static int baseS;
};

#endif
