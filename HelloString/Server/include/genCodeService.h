#ifndef GEN_CODE_SERVICE_H
#define GEN_CODE_SERVICE_H
#include "genCodeController.h"
#include <IhelloHal.h>
#include <dlfcn.h>
#include <iostream>
#include <thread>
#include <atomic>

class HelloListenerImpl : public IHelloHal::IHelloListener
{
public:
    HelloListenerImpl() { };
    HelloListenerImpl(GenCodeController *instance)
    : mController(instance) { };

    void onEvent(std::string& msg, int n) override {
        std::cout << "onEvent !" << std::endl;
        mController->getStub()->eventEmit(msg, n);
    };

private:
    GenCodeController* mController;
};

class GenCodeService {
public:
    bool startService();
    GenCodeService();
    ~GenCodeService();
    bool halOpen();
    void halsetTimeListener();

private:
    GenCodeController mStub;
    std::string mName;
    IHelloHal* mHal;
    void *handle;
};

#endif // GEN_CODE_SERVICE_H