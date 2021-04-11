/*
Env:
$uname -a
Linux chengyi-P15xEMx 4.10.0-38-generic #42~16.04.1-Ubuntu SMP Tue Oct 10 16:32:20 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux

$gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/5/lto-wrapper
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 5.4.0-6ubuntu1~16.04.11' --with-bugurl=file:///usr/share/doc/gcc-5/README.Bugs --enable-languages=c,ada,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-5 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-libmpx --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-5-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-5-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-5-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.11)
*/
#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

class Base {
  public:
    Base(int i=0) : baseI(i) {
        cout << "constructor" << endl;
    };
    int getI() {
        cout << "getI" << endl;
        return baseI;
    }
    static void countI() {
        cout << "countI" << endl;
    };
    virtual void print(void) {
        cout << "Base::print()" << endl;
    }
    virtual ~Base() {
        cout << "deconstructor" << endl;
    }
  private:
    int baseI;
    static int baseS;
};

void testBase(Base &p) {
    cout << "对象的内存起始地址: " << &p << endl;

    // MSVC实现,虚函数表前面存了指向RTTI的指针
    //cout << "type_info信息:" << endl;
    //RTTICompleteObjectLocator str = *((RTTICompleteObjectLocator*)*((uintptr_t*)*(uintptr_t*)(&p) - 1));
    //string classname(str.pTypeDescriptor->name);
    //classname = classname.substr(4, classname.find("@@") - 4);
    //cout << "根据type_info信息输出类名: " << classname << endl;

    //验证虚表
    cout << "虚函数表地址: " << (uintptr_t *)(&p) << endl;
    cout << "虚函数表第一个函数的地址: " << (uintptr_t *)*((uintptr_t*)(&p)) << endl;
    cout << "虚函数表中,第一个虚函数即print()的地址: " << (uintptr_t*)*(uintptr_t*)(&p) << endl;
    cout << "析构函数的地址: " << (uintptr_t *)((uintptr_t *)*(uintptr_t*)(&p)+1) << endl;
    cout << endl;

    typedef void(*PrintType)(void);
    PrintType IsPrint=(PrintType)* ((uintptr_t*)*(uintptr_t*)(&p));
    cout <<"调用了打印虚函数" << endl;
    //若地址正确，则调用了Base类的析构函数
    IsPrint();

    //虚函数表第二个地址是析构函数, 通过地址调用析构函数()
    typedef void(*DeconstructorType)(void*);
    DeconstructorType Deconstructor=(DeconstructorType)* ((uintptr_t*)*(uintptr_t*)(&p) + 1);
    cout <<"调用了析构虚函数" << endl;
    //若地址正确，则调用了Base类的析构函数
    Deconstructor(&p);

    //输入static函数的地址
    cout << "static函数countI()的地址: " << (uintptr_t*)p.countI << endl;

    //验证nonstatic数据成员
    cout << "推测nonstatic数据成员baseI的地址：" << (uintptr_t *)(&p) + 1 << endl;
    cout << "根据推测出的地址，输出该地址的值：" << *((uintptr_t *)(&p) + 1) << endl;
    p.getI();
}

int main(void) {
    Base b(1000);
    testBase(b);

    return 0;
}
