#include <stdio.h>
#include <iostream>
using namespace std;

class Cat
{
public:
    Cat()
    {
        cout<<"Cat类 无参构造函数"<<endl;
    }

    //Cat(Cat& obj)
    //{
    //cout<<"Cat类 拷贝构造函数"<<endl;
    //}

    ~Cat()
    {
        cout<<"Cat类 析构函数 "<<endl;
    }

};

void playStage() //一个舞台，展示对象的生命周期
{
    Cat();             /*在执行此代码时，利用无参构造函数生成了一个匿名Cat类对象；执行完此行代码，因为外部没有接此匿名对象的变量，此匿名又被析构了*/
    Cat cc = Cat();    /*在执行此代码时，利用无参构造函数生成了一个匿名Cat类对象；然后将此匿名变成了cc这个实例对象，此匿名对象没有被析构。*/
    cout<<"cc 对象好没有被析构"<<endl;
    cin.get();
}

int main()
{
    playStage();
    return 0;
}
