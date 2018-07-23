#include <iostream>
#include "Demo.h"

int abs(int arg) {
    if(arg < 0) {
        return -arg;
    }

    return arg;
}

int main() {
    Demo obj;
    obj.print();

    Demo* obj2 = new Demo;
    obj2->sayHello("chengyi");

    delete(obj2);

    return 0;
}
