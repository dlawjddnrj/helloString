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

// service는 Controller랑 hal 객체를 알고 있고

bool GenCodeService::startService()
{
    bool isHal = halOpen();
    mStub.init(mHal);

    if(isHal) {
        mStub.startService();
        std::cout << "mStub : " << &mStub << std::endl;
        std::cout << "mStub.get() " << mStub.getStub() << std::endl;

        HelloListenerImpl* mListenerImpl = new HelloListenerImpl(mStub.getStub());

        std::string abc = "Test";

        mHal->setTimeListener(mListenerImpl);
        // mHal->printMsg(abc);

        // handle은 따로 close하지 않는다. 현재 로직은 genCodeService 프로세스의 생명주기가 서버 종료까지 계속 살아있기 때문이다.
        // dlclose(handle);

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