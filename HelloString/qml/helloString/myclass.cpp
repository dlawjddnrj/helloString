#include "myclass.h"

MyClass::MyClass(QObject* parent) {}

MyClass::~MyClass() {}

void MyClass::cppSlot(const QString& msg) {
    qDebug() << "Called the C++ slot with message:" << msg;
    const std::string tempStr = msg.toStdString();
    try {
        mProxy.get()->MessageMethod_sync(tempStr, getpid());
    } catch (const Glib::Error& err) {
        std::cout << "Error What ? :" << err.what() << std::endl;
    }
    std::cout << "getStr : " << mProxy.getStr() << std::endl;
}

std::string MyClass::getStr() {
    return mProxy.getStr();
}
