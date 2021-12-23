#ifndef GEN_CODE_PROXY_H
#define GEN_CODE_PROXY_H

#include <iostream>
#include "testGenCode_proxy.h"

class GenCodeProxy {
public:
    GenCodeProxy();
    ~GenCodeProxy();

    void receiveMessageForClient(std::string s);
    void receiveTimeOccure(std::string s, int n);
    Glib::RefPtr<com::example::InterfaceProxy> get();
    void clientAreceive(std::string s);
    std::string getStr();
    int getCount();

private:
    Glib::RefPtr<com::example::InterfaceProxy> mIns;
    std::string mStr;
    int mCount = 0;
};

#endif // GEN_CODE_PROXY_H