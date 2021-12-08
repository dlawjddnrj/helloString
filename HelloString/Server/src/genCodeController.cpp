#include "../include/genCodeController.h"

GenCodeController::GenCodeController()
{
    std::cout << "GenCodeController ~~~" << std::endl;

    mConnectionId = Gio::DBus::own_name(Gio::DBus::BUS_TYPE_SESSION,
                                   "com.example.Interface",
                                   [&] (const Glib::RefPtr<Gio::DBus::Connection>& connection,
                                        const Glib::ustring& name) {
                                        std::cout << "Connected to the bus - " << name << std::endl;

                                       if (register_object(connection, "/com/example/Interface") == 0)
                                           std::cout << "Register object failed" << std::endl;
                                   },
                                   [&] (const Glib::RefPtr<Gio::DBus::Connection>& connection,
                                        const Glib::ustring& name) {
                                        std::cout << "Name acquired - " << name << std::endl;
                                   },
                                   [&] (const Glib::RefPtr<Gio::DBus::Connection>& connection,
                                        const Glib::ustring& name) {
                                        std::cout << "Name lost - " << name << std::endl;
                                   });
    std::cout << "ready !" << std::endl;
}

GenCodeController::~GenCodeController()
{
    Gio::DBus::unown_name(mConnectionId);
    std::cout << "~GenCodeController ~~~" << std::endl;
}

void GenCodeController::MessageMethod(const Glib::ustring& message,
                                      gint32 callerPid,
                                      MethodInvocation& invocation)
{
    std::cout << "received Message : (" << message << ") -From callerPid : " << callerPid << std::endl;
    invocation.ret();
    notify_signal.emit(message);
}

bool GenCodeController::startService()
{
    std::cout << "GenCodeController::startService !" << std::endl;
    return true;
}

void GenCodeController::eventEmit(const Glib::ustring& message) {
    // bus 연결 확인 1이 아닌 값은 연결되지 않는 값.
    // if(mConnectionId == 1) {
        notify_signal.emit(message);
    // }
}