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
    mStub.init(mHal);

    if(isHal) {
        mStub.startService();

        HelloListenerImpl* mListenerImpl = new HelloListenerImpl(mStub.getStub());

        std::string abc = "Test";

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