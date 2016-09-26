#include <stdio.h>

class aclass {
    private:
        int m;
        char c;
    public:
        aclass(int i, char ch) {
            printf("Constructor called\n");
            this->m = i;
            this->c = ch;
        }
        ~aclass() {
            printf("Destructor called\n");
        }
        int getM() const {
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
            printf("%d\n", a+b);
            return a+b;
        }
};

int main(void)
{
    aclass *a = new aclass(3, 'c');
    a->setM(5);
    a->setC('a');
    a->add(2, 8);
    printf("%d\n", a->getM());    return 0;
    delete a;
    return 0;
}
