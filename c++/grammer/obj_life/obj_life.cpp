#include <iostream>
#include <string.h>
using namespace std;

class A {
    char string[50];
public :
    A(const char * st);
    ~A( );
};

A::A(const char * st)
{
    strcpy(string, st);
    cout << string << "-->C.被创建时调用构造函数 ! " << endl;
}

A::~A( )
{
    cout << string <<
        "-->D.被撤消时调用析构函数 ! " << endl;
}

void fun( )
{
    cout << "1.在fun( )函数体内 : \n" << endl;
    A FunObj("2.fun( )函数体内的自动对象FunObj");
    static A InStaObj("3.内部静态对象InStaObj");
}

int main( )
{
    A MainObj("4.主函数体内的自动对象MainObj");
    cout<<"5.主函数体内，调用fun()函数前: \n";
    fun( );
    cout << "\n6.主函数体内，调用fun()函数后:\n";

    return 0;
}

static A ExStaObj("7.外部静态对象ExStaObj");
A GblObj("8.外部对象GblObj");
