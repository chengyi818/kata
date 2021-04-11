#include <iostream>
#include <cstdint>
using namespace std;

class Base {
    public:
        Base(int i=0) :baseI(i){ cout << "调用了基类Base的构造函数" << endl; };
        virtual void print(void){ cout << "调用了虚函数Base::print()" << endl; }
        virtual void setI(){cout<<"调用了虚函数Base::setI()" << endl;}
        virtual ~Base(){}

    private:
        int baseI;
};
class Drive1 :public Base {
    public:
        virtual void print(void) {};
};
class Drive2 :public Base {
    public:
        virtual void print(void) {};
};


int main(void)
{
    Base * ptr1 = new Base;
    Base * ptr2 = new Drive1;
    Base * ptr3 = new Drive2;

    ptr1->print(); //调用Base::print()
    ptr2->print();//调用Drive1::print()
    ptr3->print();//调用Drive2::print()

    cout << "*****************************************LINE:"<< __LINE__ << endl;

    Base b(1000);
    uintptr_t * vptrAdree = (uintptr_t *)(&b);
    cout << "虚函数指针（vptr）的地址是：\t"<<vptrAdree << endl;

    cout << "*****************************************LINE:"<< __LINE__ << endl;

    typedef void(*Fun)(void);
    Fun vfunc = (Fun)*( (uintptr_t *)*(uintptr_t*)(&b));
    cout << "第一个虚函数的地址是：" << (uintptr_t *)*(uintptr_t*)(&b) << endl;
    cout << "通过地址，调用虚函数Base::print()：" << endl;
    vfunc();

    Fun vfunc_2 = (Fun)*( (uintptr_t *)*(uintptr_t*)(&b) + 1);
    cout << "第二个虚函数的地址是：" << (uintptr_t *)*(uintptr_t*)(&b) + 1 << endl;
    cout << "通过地址，调用虚函数Base::setI()：" << endl;
    vfunc_2();

    cout << "*****************************************LINE:"<< __LINE__ << endl;

    return 0;
}
