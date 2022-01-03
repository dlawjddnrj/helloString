#ifndef HELLO_HAL_H
#define HELLO_HAL_H
#include "IhelloHal.h"
#include <functional>
#include <thread>
#include <atomic>

class HelloHal : public IHelloHal {
public:
    void setTimeListener(IHelloListener *listener) override;
    void printMsg(std::string str) override;
    void timerRun();

private:
    IHelloListener* mListener = nullptr;
    int timerCount = 0;
};

#endif // HELLO_HAL_H