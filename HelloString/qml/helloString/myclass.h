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
signals:
    void timerChanged(int count);

public slots:
    void cppSlot(const QString& msg);
    QString getStr();
    void testFunc(QString);
    void timerCount();

public:
    GenCodeProxy mProxy;
};

#endif  // MYCLASS_H
