#include "Application.h"
#include "Win32EventQueue.h"
#include "Object.h"
#include "Event.h"

bool Application::shouldKeepRunning = true;

Application::Application()
:   eventQueue{new Win32EventQueue}
{}

Application::~Application() {
    delete eventQueue;
}

uint64_t
Application::run() {
    while(Application::shouldKeepRunning) {
        Event * event = eventQueue->nextEvent();
        assert(event);
        assert(EventQueue::currentReceiver);
        if (EventQueue::currentReceiver && event)
            sendEvent(EventQueue::currentReceiver, event);
    }
    return 0;
}

void
Application::sendEvent(Object * receiver, Event * event) {
    std::cout << "Application::sendEvent \n";
    assert(receiver);
    assert(event);
    receiver->handleEvent(event);
}
