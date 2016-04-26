#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> intVector(100);

int main()
{
    intVector[20] = 50;

    vector<int>::iterator first;
    first = intVector.begin();
    *first = 123;

    //const vector<int>::iterator result;
    //result = find(intVector.begin(), intVector.end(), 50);
    //if (result != intVector.end())
        //*result = 123;   ???



    vector<int>::iterator intIter =
        find(intVector.begin(), intVector.end(), 50);
    if (intIter != intVector.end())
        cout << "Vector contains value " << *intIter << endl;
    else
        cout << "Vector does not contain 50" << endl;

    return 0;
}
