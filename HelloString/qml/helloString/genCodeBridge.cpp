#include "genCodeBridge.h"

GenCodeBridge::GenCodeBridge(QObject* parent) {}

GenCodeBridge::~GenCodeBridge() {}

void GenCodeBridge::testFunc(QString getStr) {
    qDebug() << "testFunc Call !, " << getStr;
}

void GenCodeBridge::timerCount() {
    qDebug() << "getCount : " << mProxy.getCount();
    emit this->timerChanged(mProxy.getCount());
}

void GenCodeBridge::cppSlot(const QString& msg) {
    qDebug() << "Called the C++ slot with message:" << msg;
    const std::string tempStr = msg.toStdString();
    try {
        mProxy.get()->MessageMethod_sync(tempStr, getpid());
    } catch (const Glib::Error& err) {
        std::cout << "Error What ? :" << err.what() << std::endl;
    }
}

QString GenCodeBridge::getStr() {
    QString temp = QString::fromStdString(mProxy.getStr());
    return temp;
}
