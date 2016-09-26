#include <stdio.h>
#include <iostream>
using namespace std;

class aclass {
    private:
        int m;
        char c;
    public:
        aclass(int i, char ch) {
            cout << "Constructor called" << endl;
            this->m = i;
            this->c = ch;
        }
        ~aclass() {
            cout << "Destructor called" << endl;
        }
        int getM() const {
            cout << m << endl;
            return m;
        }
        void setM(int m) {
            this->m = m;
        }
        char getC() const {
            return c;
        }
        void setC(char c) {
            this->c = c;
        }
        int add(int a, int b) {
            cout<< "a+b:" << a+b << endl;
            return a+b;
        }
};

int main(void)
{
    aclass *a = new aclass(3, 'c');
    a->setM(5);
    a->setC('a');
    a->add(2, 8);
    a->getM();
    delete a;
    return 0;
}
