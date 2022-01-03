#ifndef GenCodeBridge_H
#define GenCodeBridge_H

#include <genCodeProxy.h>
#include <QDebug>
#include <QObject>

class GenCodeBridge : public QObject {
    Q_OBJECT
public:
    explicit GenCodeBridge(QObject* parent = 0);
    ~GenCodeBridge();
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

#endif  // GenCodeBridge_H
