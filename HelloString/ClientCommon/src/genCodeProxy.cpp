#include "../include/genCodeProxy.h"

GenCodeProxy::GenCodeProxy()
{
    std::cout << "GenCodeProxy() !" << std::endl;
    mIns = com::example::InterfaceProxy::createForBus_sync(Gio::DBus::BUS_TYPE_SESSION,
                                                           Gio::DBus::PROXY_FLAGS_NONE,
                                                           "com.example.Interface",
                                                           "/com/example/Interface");

    mIns->notify_signal.connect(sigc::mem_fun(this, &GenCodeProxy::receiveMessageForClient));
    // mIns->notify_signal.connect(sigc::mem_fun(this, &GenCodeProxy::clientAreceive));
    mIns->timerOccure_signal.connect(sigc::mem_fun(this, &GenCodeProxy::receiveTimeOccure));
}

GenCodeProxy::~GenCodeProxy()
{
    std::cout << "~GenCodeProxy() ~" << std::endl;
}

Glib::RefPtr<com::example::InterfaceProxy> GenCodeProxy::get()
{
    return mIns;
}

void GenCodeProxy::receiveMessageForClient(std::string s)
{
    mStr = s;
    std::cout << "receiveMessageForClient : " << s << std::endl;
}

void GenCodeProxy::receiveTimeOccure(std::string s, int n) {
    mCount = n;
    std::cout << "receiveTimeOccure : " << s << ", time occure count : " << n << std::endl;
}

// get이 아닌 timerOccure_signal.connect 에서 함수를 등록한 후 qml로 보내는 것을 구현

void GenCodeProxy::clientAreceive(std::string s) {
    std::cout << "clientAreceive : " << mStr << std::endl;
}

std::string GenCodeProxy::getStr() {
    return mStr;
}

int GenCodeProxy::getCount() {
    return mCount;
}