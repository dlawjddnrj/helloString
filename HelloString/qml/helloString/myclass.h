#ifndef MYCLASS_H
#define MYCLASS_H

#include <genCodeProxy.h>
#include <QDebug>
#include <QObject>

class MyClass : public QObject {
    Q_OBJECT
public:
    explicit MyClass(QObject* parent = 0);
    ~MyClass();
public slots:
    void cppSlot(const QString& msg);
    std::string getStr();

public:
    GenCodeProxy mProxy;
};

#endif  // MYCLASS_H
