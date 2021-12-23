#include <iostream>
#include "genCodeProxy.h"
#include "threadExClass.h"

using namespace com;
using namespace com::example;

int main(void) {
    try {
        Glib::init();
        Gio::init();
        Glib::RefPtr<Glib::MainLoop> loop = Glib::MainLoop::create();

    std::cout << "Client B!" << std::endl;

    GenCodeProxy a;

    loop->run();
    } catch(const Glib::Error& err) {
        std::cout << "what Error ? : " << err.what() << std::endl;
    }
    return 0;
}
