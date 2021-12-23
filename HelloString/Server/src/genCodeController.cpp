#include "../include/genCodeController.h"

GenCodeController::GenCodeController()
{
    std::cout << "GenCodeController ~~~" << std::endl;
}

GenCodeController::~GenCodeController()
{
    Gio::DBus::unown_name(mConnectionId);
    std::cout << "~GenCodeController ~~~" << std::endl;
}

void GenCodeController::init(IHelloHal *hal) {
    mHal = hal;
    std::cout << "init !" << std::endl;
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

void GenCodeController::MessageMethod(const Glib::ustring& message,
                                      gint32 callerPid,
                                      MethodInvocation& invocation)
{
    std::cout << "received Message : (" << message << ") -From callerPid : " << callerPid << std::endl;
    invocation.ret();
    notify_signal.emit(message);
    mHal->printMsg(message);
}

bool GenCodeController::startService()
{
    std::cout << "GenCodeController::startService !" << std::endl;
    return true;
}

void GenCodeController::eventEmit(const Glib::ustring& message, const gint32 n) {
    timerOccure_signal.emit(message, n);
}

GenCodeController* GenCodeController::getStub() {
    return this;
}