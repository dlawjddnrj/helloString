#include "../include/genCodeService.h"

GenCodeService::GenCodeService() {
    std::cout << "GenCodeService..." << std::endl;
}

bool GenCodeService::halOpen() {
    void *handle = NULL;

    handle = dlopen("/opt/test/lib/libhelloHal.so", RTLD_LAZY);

    if(!handle) {
        std::cout << "dlopen error what ? : " << dlerror() << std::endl;
        return false;
    }
    mHal = (IHelloHal*) dlsym(handle, HELLO_INSTANCE_STR);

    if(!mHal) {
        std::cout << "dlsym error what ? : " << dlerror() << std::endl;
        return false;
    }
    return true;
}

bool GenCodeService::startService()
{
    bool isHal = halOpen();

    if(isHal) {
        mStub.init(mHal);
        mStub.startService();

        HelloListenerImpl* mListenerImpl = new HelloListenerImpl(mStub.getStub());

        mHal->setTimeListener(mListenerImpl);

        std::cout << "GenCodeService::startService()" << std::endl;
        return true;
    } else {
        return false;
    }
}

GenCodeService::~GenCodeService()
{
    std::cout << "~GenCodeService ~" << std::endl;
}