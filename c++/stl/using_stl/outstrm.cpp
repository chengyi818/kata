#include <iostream>
#include <stdlib.h>    // Need random(), srandom()
#include <time.h>      // Need time()
#include <algorithm>   // Need sort(), copy()
#include <vector>      // Need vector

using namespace std;

void Display(vector<int>& v, const char* s);

int main()
{
    // Seed the random number generator
    srandom( time(NULL) );

    // Construct vector and fill with random integer values
    vector<int> collection(10);
    for (int i = 0; i < 10; i++)
        collection[i] = random() % 10000;;

    // Display, sort, and redisplay
    Display(collection, "Before sorting");
    sort(collection.begin(), collection.end());
    Display(collection, "After sorting");
    return 0;
}

// Display label s and contents of integer vector v
void Display(vector<int>& v, const char* s)
{
    cout << endl << s << endl;
    copy(v.begin(), v.end(),
            ostream_iterator<int>(cout, "\t"));
    cout << endl;
}
