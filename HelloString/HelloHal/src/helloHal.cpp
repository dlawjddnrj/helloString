#include "../include/helloHal.h"
#include <unistd.h>

void HelloHal::setTimeListener(IHelloListener *listener) {
    std::cout << "setTimeListener !" << std::endl;
    mListener = listener;

    std::thread threadTemp(&HelloHal::timerRun, this);
    threadTemp.detach();
}

void HelloHal::printMsg(std::string str) {
    std::cout << "printMsg : " << str << std::endl;
}

void HelloHal::timerRun() {
    std::string tempstr = "timer occure";
    timerCount = -1;
    while (1) {
        if(mListener) {
            timerCount += 1;
            mListener->onEvent(tempstr, timerCount);
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

// dlsym으로 define 명령어를 이용하여 객체를 사용하는 것이다.
// genCodeService.cpp의 *hal이 아래의 객체를 사용한다.
HelloHal HELLO_INSTANCE;