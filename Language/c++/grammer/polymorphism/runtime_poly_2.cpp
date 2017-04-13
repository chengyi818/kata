#include <iostream>
#include <vector>
using namespace std;

class Animal
{
    public :
        virtual void shout() = 0;
};

class Dog :public Animal
{
    public:
        //virtual void shout(){ cout << "汪汪！"<<endl; }
        void shout(){ cout << "汪汪！"<<endl; }
};

class Cat :public Animal
{
    public:
        //virtual void shout(){ cout << "喵喵~"<<endl; }
        void shout(){ cout << "喵喵~"<<endl; }
};

class Bird : public Animal
{
    public:
        //virtual void shout(){ cout << "叽喳!"<<endl; }
        void shout(){ cout << "叽喳!"<<endl; }
};

int main()
{
    vector<Animal*>anims;

    Animal * anim1 = new Dog;
    Animal * anim2 = new Cat;
    Animal * anim3 = new Bird;
    Animal * anim4 = new Dog;
    Animal * anim5 = new Cat;
    Animal * anim6 = new Bird;
    //处理异质类集合
    anims.push_back(anim1);
    anims.push_back(anim2);
    anims.push_back(anim3);
    anims.push_back(anim4);
    anims.push_back(anim5);
    anims.push_back(anim6);
    for (auto & i : anims)
    {
        i->shout();
    }

    //delete对象
    //...

    return 0;
}
