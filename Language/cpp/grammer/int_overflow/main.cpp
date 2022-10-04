#include <iostream>

using namespace std;

typedef unsigned char UWORD8;
typedef unsigned short UWORD16;

int main(void)
{
    UWORD16 total;
    UWORD8 nums;

    nums = 255;
    total = 65535;
    for(int i=0; i < 5; i++)
        {
            total++;
            cout << total << endl;
        }

    return 0;
}
