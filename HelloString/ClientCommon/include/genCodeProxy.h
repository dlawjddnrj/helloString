#ifndef GEN_CODE_PROXY_H
#define GEN_CODE_PROXY_H

#include <iostream>
#include "testGenCode_proxy.h"

class GenCodeProxy {
public:
    GenCodeProxy();
    ~GenCodeProxy();

    void receiveMessageForClient(std::string s);
    Glib::RefPtr<com::example::InterfaceProxy> get();
    void clientAreceive(std::string s);
    std::string getStr();

private:
    Glib::RefPtr<com::example::InterfaceProxy> mIns;
    std::string mStr;
};

#endif // GEN_CODE_PROXY_H