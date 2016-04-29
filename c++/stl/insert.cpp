#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

int iArray[5] = { 1, 2, 3, 4, 5 };

void Display(list<int>& v, const char* s);

int main()
{
     list<int> iList;

         // Copy iArray backwards into iList
         copy(iArray, iArray + 5, front_inserter(iList));
     Display(iList, "Before find and copy");

         // Locate value 3 in iList
         list<int>::iterator p =
         find(iList.begin(), iList.end(), 3);

         // Copy first two iArray values to iList ahead of p
         copy(iArray, iArray + 2, inserter(iList, p));
     Display(iList, "After find and copy");

         return 0;
}

void Display(list<int>& a, const char* s)
{
     cout << s << endl;
     copy(a.begin(), a.end(),
             ostream_iterator<int>(cout, " "));
     cout << endl;
}
