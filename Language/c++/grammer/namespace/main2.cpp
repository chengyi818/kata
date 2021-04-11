#include <cstddef>
#include <iostream>
using namespace std;

template < typename T >
class shared_ptr {
  private:
    class implement { // 实现类，引用计数
      public:
        implement(T* pp):p(pp),refs(1) {}

        ~implement() {
            delete p;
        }

        T* p; // 实际指针
        size_t refs; // 引用计数
    };
    implement* _impl;

  public:
    explicit shared_ptr(T* p)
        :  _impl(new implement(p)) {}


    ~shared_ptr() {
        decrease();  // 计数递减
    }


    shared_ptr(const shared_ptr& rhs)
        :  _impl(rhs._impl) {
        increase();  // 计数递增
    }

    shared_ptr& operator=(const shared_ptr& rhs) {
        if (_impl != rhs._impl) { // 避免自赋值
            decrease();  // 计数递减，不再共享原对象
            _impl=rhs._impl;  // 共享新的对象
            increase();  // 计数递增，维护正确的引用计数值
        }
        return *this;
    }

    T* operator->() const {
        return _impl->p;
    }

    T& operator*() const {
        return *(_impl->p);
    }

  private:
    void decrease() {
        if (--(_impl->refs)==0) {
            // 不再被共享，销毁对象
            delete _impl;
        }
    }

    void increase() {
        ++(_impl->refs);
    }
};

void foo1(shared_ptr < int >& val) {
    shared_ptr < int > temp(val);
    *temp=300;
}

void foo2(shared_ptr < int >& val) {
    val=shared_ptr < int > ( new int(200) );
}

int main() {
    shared_ptr < int > val(new int(100));
    std::cout<<"val="<<*val;
    foo1(val);
    std::cout<<"val="<<*val;
    foo2(val);
    std::cout<<"val="<<*val;
}
