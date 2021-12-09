#ifndef GEN_CODE_CONTROLLER_H
#define GEN_CODE_CONTROLLER_H

#include <iostream>
#include <IhelloHal.h>
#include <dlfcn.h>
#include "testGenCode_stub.h"

class GenCodeController : public com::example::InterfaceStub {
public:
    GenCodeController();
    ~GenCodeController();
    void init();

    // MessageMethod로 받음
    void MessageMethod(const Glib::ustring & message,
                       gint32 callerPid,
                       MethodInvocation &invocation) override;
    bool startService();
    void eventEmit(const Glib::ustring& message);
    GenCodeController* getStub();

private:
    // gdbus
    guint mConnectionId;
    std::vector<Glib::ustring> mProxyList;
    std::map<std::string, guint> mProxyWatchId;
};

#endif // GEN_CODE_CONTROLLER_H