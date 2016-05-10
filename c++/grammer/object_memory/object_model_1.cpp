#include <iostream>
#include <cstdint>
using namespace std;

class Base
{
    public:
        Base(int i=0) : baseI(i) {};
        int getI(){ return baseI; }
        static void countI(){};
        virtual void print(void){ cout << "Base::print()"; }
        virtual ~Base(){}
    private:
        int baseI;
        static int baseS;
};

void testBase(Base &p)
{
    cout << "对象的内存起始地址：" << &p << endl;

    //cout << "type_info信息:" << endl;
    //RTTICompleteObjectLocator str = *((RTTICompleteObjectLocator*)*((uintptr_t*)*(uintptr_t*)(&p) - 1));
    //string classname(str.pTypeDescriptor->name);
    //classname = classname.substr(4, classname.find("@@") - 4);
    //cout <<  "根据type_info信息输出类名:"<< classname << endl;


    cout << "虚函数表地址:" << (uintptr_t *)(&p) << endl;
    //验证虚表
    cout << "虚函数表第一个函数的地址：" << (uintptr_t *)*((uintptr_t*)(&p)) << endl;

    cout << "析构函数的地址:" << (uintptr_t* )*(uintptr_t *)*((uintptr_t*)(&p)) << endl;

    cout << "虚函数表中，第二个虚函数即print（）的地址：" << ((uintptr_t*)*(uintptr_t*)(&p) + 1) << endl;
    //通过地址调用虚函数print（）
    typedef void(*Fun)(void);
    Fun IsPrint=(Fun)* ((uintptr_t*)*(uintptr_t*)(&p) + 1);

    cout << endl;

    cout <<"调用了虚函数" << endl;
        IsPrint(); //若地址正确，则调用了Base类的虚函数print（）
    cout << endl;
    //输入static函数的地址
    p.countI();//先调用函数以产生一个实例
    cout << "static函数countI()的地址：" << p.countI << endl;
    //验证nonstatic数据成员
    cout << "推测nonstatic数据成员baseI的地址：" << (uintptr_t *)(&p) + 1 << endl;        cout << "根据推测出的地址，输出该地址的值：" << *((uintptr_t *)(&p) + 1) << endl;

    cout << "Base::getI():" << p.getI() << endl;
}

int main(void)
{
    Base b(1000);
    testBase(b);

     return 0;
}
