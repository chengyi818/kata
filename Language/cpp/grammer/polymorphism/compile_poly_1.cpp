#include <iostream>
#include <stdio.h>
using namespace std;
class Animal
{
    public :
        void shout() { cout << "发出动物的叫声" << endl; };
};

class Dog
{
    public:
        void shout(){ cout << "汪汪！"<<endl; }
};

class Cat
{
    public:
        void shout(){ cout << "喵喵~"<<endl; }
};

class Bird
{
    public:
        void shout(){ cout << "叽喳!"<<endl; }
};

template <typename T>

void  animalShout(T & t)
{
    t.shout();
}

int main()
{
    Animal anim;
    Dog dog;
    Cat cat;
    Bird bird;

    animalShout(anim);
    animalShout(dog);
    animalShout(cat);
    animalShout(bird);

    getchar();
}
