#include <cstring>
#include <memory>
#include <iostream>

class string {
  public:
    string(const char* cstr) {
        _data=new char [ strlen(cstr)+1 ];
        strcpy(_data, cstr);
    }
    ~string() {
        delete [] _data;
    }
    const char* c_str() const {
        return _data;
    }
  private:
    char* _data;
};

int main() {
    ::std::auto_ptr<string> str(new string("hello"));
    ::std::cout << str->c_str() << ::std::endl;
    return 0;
}
