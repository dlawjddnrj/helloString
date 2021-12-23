#include "myclass.h"

MyClass::MyClass(QObject* parent) {}

MyClass::~MyClass() {}

void MyClass::testFunc(QString getStr) {
    qDebug() << "testFunc Call !, " << getStr;
}

void MyClass::timerCount() {
    qDebug() << "getCount : " << mProxy.getCount();
    emit this->timerChanged(mProxy.getCount());
}

void MyClass::cppSlot(const QString& msg) {
    qDebug() << "Called the C++ slot with message:" << msg;
    const std::string tempStr = msg.toStdString();
    try {
        mProxy.get()->MessageMethod_sync(tempStr, getpid());
    } catch (const Glib::Error& err) {
        std::cout << "Error What ? :" << err.what() << std::endl;
    }
}

QString MyClass::getStr() {
    QString temp = QString::fromStdString(mProxy.getStr());
    return temp;
}
