#include "IMyService.h"

int main() {
    //��ȡservice manager����
	sp<IServiceManager> sm = defaultServiceManager();
    //ע����Ϊ"service.myservice"�ķ���service manager
	sm->addService(String16("service.myservice"), new BnMyService());
    //�����̳߳�
	ProcessState::self()->startThreadPool();
    //�����̼߳����̳߳�
	IPCThreadState::self()->joinThreadPool();
	return 0;
}
