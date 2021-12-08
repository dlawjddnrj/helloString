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
    HelloListenerImpl();
    HelloListenerImpl(GenCodeController *instance);

    void onEvent(std::string& msg) override;
private:
    GenCodeController* mController;
};

class GenCodeService {
public:
    static GenCodeService& getInstance();
    bool startService();
    GenCodeService();
    ~GenCodeService();
    void halOpen();
    void halsetTimeListener();

private:
    std::shared_ptr<GenCodeController> mStub = nullptr;
    std::shared_ptr<HelloListenerImpl> mListenerImpl = nullptr;
    std::string mName;
    IHelloHal* mHal;
};

#endif // GEN_CODE_SERVICE_H