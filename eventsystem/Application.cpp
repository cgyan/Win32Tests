#include "Application.h"
#include "Win32RunLoop.h"
#include "Object.h"
#include "Event.h"

Application::Application()
:   runLoop{new Win32RunLoop}
{}

Application::~Application() {
    delete runLoop;
}

uint64_t
Application::run() {
    RunLoop::start();
    while(RunLoop::isRunning()) {
        runLoop->processNextEvent();
    }
    return 0;
}

void
Application::sendEvent(Object * receiver, Event * event) {
    assert(receiver);
    assert(event);
    receiver->handleEvent(event);
}
