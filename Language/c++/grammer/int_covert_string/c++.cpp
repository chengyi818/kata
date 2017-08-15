/*
 * File Name: c++.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 02 Aug 2017 10:45:30 AM CST
 */
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

string int2str(int &);
static void hex_to_str(char *ptr,unsigned char *buf,int len);

int main(void) {
    int i = 0xba76;
    string s1;
    s1 = int2str(i);
    cout << "s1: " << s1 << endl;
    const char* s1_2 = s1.c_str();
    printf("s1: %s\n", s1_2);


    char* test = "a";
    if(test) {
        printf("test true");
    }

}

string int2str(int &i) {
    string s;
    stringstream ss(s);
    ss << i;

    return ss.str();
}


static void hex_to_str(char *ptr,unsigned char *buf,int len)
{
    for(int i = 0; i < len; i++)
    {
        sprintf(ptr, "%02x",buf[i]);
        ptr += 2;
    }
}
