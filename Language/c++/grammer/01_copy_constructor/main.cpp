#include <iostream>

using namespace std;

class A {
  public:
    A() {
        cout << "default constructor" <<endl;
    }

    A(const A& other) {
        cout << "copy constructor" <<endl;
        data = other.data;
    }

    ~A() {
        cout << "deconstructor" << endl;
    }

    A(int i): data(i) {
        cout << "parameter  constructor" << endl;
    }

    A& operator = (const A& other) {
        cout << "copy operator" <<endl;
        if(this == &other) {
            return *this;
        }
        data = other.data;
        return *this;
    }

    int getData() {
        return data;
    }


  private:
    int data;
};

A Play(A a) {
    cout << "Play" << endl;
    return a;
}

int main() {
    //对象传入,隐式转换, 调用带参构造函数
    //对象传出, 调用复制构造函数
    A t1 = Play(5);
    cout << "t1: " << t1.getData() << endl;
    cout << "-------------------" << endl;

    // 对象传入,复制构造函数
    //对象传出, 调用复制构造函数
    A t2 = Play(t1);
    cout << "t2: " << t2.getData() << endl;
    cout << "-------------------" << endl;

    // 带参构造函数
    A t3(5);
    // 复制构造函数
    A t4(t3);

    cout << "-------------------" << endl;
    A t5;
    // 赋值拷贝
    t5=t4;

    cout << "-------------------" << endl;
    return 0;
}
