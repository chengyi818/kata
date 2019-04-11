#include "IMyService.h"

int main() {
    //获取service manager引用
    sp<IServiceManager> sm = defaultServiceManager();
    //获取名为"service.myservice"的binder接口
    sp<IBinder> binder = sm->getService(String16("service.myservice"));
    //将biner对象转换为强引用类型的IMyService
    sp<IMyService> cs = interface_cast<IMyService>(binder);
    //利用binder引用调用远程sayHello()方法
    cs->sayHello();
    return 0;
}
