#ifndef I_HELLO_HAL_H
#define I_HELLO_HAL_H
#define HELLO_INSTANCE HELLOHALINSTANCE
#define HELLO_INSTANCE_STR "HELLOHALINSTANCE"
#include <iostream>

class IHelloHal {
public:
    class IHelloListener {
        public:
            virtual void onEvent(std::string& msg) = 0;
    };

    virtual void setTimeListener(IHelloListener *listener) = 0;
    virtual void printMsg(std::string str) = 0;
    
};

#endif // I_HELLO_HAL_H