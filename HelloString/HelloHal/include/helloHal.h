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
    // void onEvent(std::string& msg) override;

private:
    IHelloListener* mListener = nullptr;
};

#endif // HELLO_HAL_H