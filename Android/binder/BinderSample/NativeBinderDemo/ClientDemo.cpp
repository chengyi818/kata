#include "IMyService.h"

int main() {
    //��ȡservice manager����
    sp<IServiceManager> sm = defaultServiceManager();
    //��ȡ��Ϊ"service.myservice"��binder�ӿ�
    sp<IBinder> binder = sm->getService(String16("service.myservice"));
    //��biner����ת��Ϊǿ�������͵�IMyService
    sp<IMyService> cs = interface_cast<IMyService>(binder);
    //����binder���õ���Զ��sayHello()����
    cs->sayHello();
    return 0;
}
