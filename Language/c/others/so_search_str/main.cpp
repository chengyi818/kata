/*
 * File Name: main.cpp
 * Author: ChengYi
 * Mail: chengyi@antiy.cn
 * Created Time: Mon 20 Jun 2016 04:25:36 PM CST
 */

/*
  Step 1: open .so file
  Step 2: malloc a buffer
  Step 3: copy content from .so to buffer
  Step 4: KMP search string in buffer
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int main(int argc, char *argv[])
{

	string string_ToBeSearched = "chengyi test";

	ifstream in("libfunc.so", ios::in);
	if(!in.is_open()) {
		cout << "File opening failed" << endl;
		return 1;
	}
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);
	in.close();

	int result = strdata.find(string_ToBeSearched);
	if(result == string::npos)
	{
		cout << "not found" << endl;
	}

    return 0;
}


