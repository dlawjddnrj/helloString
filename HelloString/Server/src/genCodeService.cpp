#include "../include/genCodeService.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

struct passwd *pw = getpwuid(getuid());
char *homedir = pw->pw_dir;
char *halPath = "/hello/lib/libhelloHal.so";

void HelloListenerImpl::onEvent(std::string& msg) {
        std::cout << "onEvent !" << std::endl;
        mController->eventEmit(msg);
}

HelloListenerImpl::HelloListenerImpl() { }

HelloListenerImpl::HelloListenerImpl(GenCodeController *instance)
    : mController(instance) { }

GenCodeService::GenCodeService() {
    std::cout << "GenCodeService..." << std::endl;
}

GenCodeService &GenCodeService::getInstance()
{
    static GenCodeService instance;
    return instance;
}

bool GenCodeService::startService()
{
    mStub = std::make_shared<GenCodeController>();
    mStub->startService();

    // mStub의 주소를 넘겨주지 않아서 기본 생성자가 생성되어 mController 객체가 비어있었음.
    mListenerImpl = std::make_shared<HelloListenerImpl>(mStub.get());

    std::string abc = "Test";

    void *handle = NULL;

    strcat(homedir, halPath);

    handle = dlopen(homedir, RTLD_LAZY);

    if(!handle) {
        std::cout << "dlopen error what ? : " << dlerror() << std::endl;
        return false;
    }

    IHelloHal* hal = (IHelloHal*) dlsym(handle, HELLO_INSTANCE_STR);
    hal->setTimeListener(mListenerImpl.get());

    if(!hal) {
        std::cout << "dlopen error what ? : " << dlerror() << std::endl;
        return false;
    }

    hal->printMsg(abc);

    // dlclose(handle);

    std::cout << "GenCodeService::startService()" << std::endl;
    return true;
}

GenCodeService::~GenCodeService()
{
    std::cout << "~GenCodeService ~" << std::endl;
}