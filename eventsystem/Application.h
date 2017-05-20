#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <cstdint>
#include <windows.h>
#include <iostream>
class EventQueue;
class Object;
class Widget;
class Event;

class Application {
private:
    EventQueue * eventQueue;
public:
    static bool shouldKeepRunning;
public:
    Application();
    ~Application();
    static void sendEvent(Object * receiver, Event * event);
    uint64_t run();
};

#endif // APPLICATION_H_
