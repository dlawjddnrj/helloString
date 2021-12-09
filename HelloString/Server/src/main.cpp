#include <iostream>
#include "genCodeService.h"

int main(void) {
    Glib::init();
    Gio::init();
    Glib::RefPtr<Glib::MainLoop> loop = Glib::MainLoop::create();
    std::cout << "Server main() !!!" << std::endl;

    GenCodeService serverService;
    bool isService = serverService.startService();

    if(!isService) {
        std::cout << "Error... Not true" << std::endl;
        return 0;
    }

    loop->run();

    return 0;
}
