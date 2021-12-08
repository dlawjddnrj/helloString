#include <iostream>
#include "genCodeProxy.h"
#include "threadExClass.h"

using namespace com;
using namespace com::example;

void clientInput(GenCodeProxy proxyArg, Glib::RefPtr<Glib::MainLoop> loopArg)
{
    while (1)
    {
        char inputData[100];
        char exit[10] = "exit";
        char Exit[10] = "Exit";
        char EXIT[10] = "EXIT";
        std::cout << "send to Message : ";
        std::cin.getline(inputData, 100);

        if (strcmp(inputData, exit) == 0 || strcmp(inputData, Exit) == 0 || strcmp(inputData, EXIT) == 0)
        {
            std::cout << "EXIT... Pls" << std::endl;
            loopArg->quit();
        }

        try {
            proxyArg.get()->MessageMethod_sync(inputData, getpid());
        } catch(const Glib::Error& err) {
            std::cout << "Error What ? : " << err.what() << std::endl;
        }
    }
}

int main(void)
{
    Glib::init();
    Gio::init();
    Glib::RefPtr<Glib::MainLoop> loop = Glib::MainLoop::create();
    std::cout << "Client A!" << std::endl;

    GenCodeProxy proxy;

    std::thread threadHandler(clientInput, std::ref(proxy), std::ref(loop));

    threadHandler.detach();
    loop->run();
    return 0;
}
