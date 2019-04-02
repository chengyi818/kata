#include "IMyService.h"

int main() {
    //获取service manager引用
	sp<IServiceManager> sm = defaultServiceManager();
    //注册名为"service.myservice"的服务到service manager
	sm->addService(String16("service.myservice"), new BnMyService());
    //启动线程池
	ProcessState::self()->startThreadPool();
    //把主线程加入线程池
	IPCThreadState::self()->joinThreadPool();
	return 0;
}
