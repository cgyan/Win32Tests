#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <windows.h>
#include "Win32EventQueue.h"
class Event;

class Application {
private:
    EventQueue eventQueue;
public:
    Application();
    uint64_t run();
};

Application::Application()
:   eventQueue{new Win32EventQueue}
{}

uint64_t
Application::run() {
    std::cout << "application running \n";
    while(true) {
        Event * event = eventQueue.nextEvent();
    }
    // MSG msg;
    //
    // while (GetMessage(&msg, NULL, 0, 0)) {
    //     TranslateMessage(&msg);
    //     DispatchMessage(&msg);
    // }
    // return msg.wParam;
}

#endif // APPLICATION_H_
