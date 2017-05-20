#ifndef PRISMEVENTDISPATCHER_H_
#define PRISMEVENTDISPATCHER_H_

#include <windows.h>
#include "Event.h"
#include "Object.h"
#include <map>
#include <list>
#include <iostream>
#include <algorithm>

class EventDispatcher {
public:
    using EventList = std::list<Event::Type>;
private:
    using Object2EventMap = std::map<const Object*, EventList>;
    using Iter = Object2EventMap::iterator;
    Object2EventMap ob2evMap;
public:
    static LRESULT CALLBACK dispatcher(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    static EventDispatcher& instance();
private:
    EventDispatcher();
    const bool objectRegisteredForEvent(Object * obj, Event::Type etype);
public:
    void registerObjectForEvent(const Object * object, Event::Type etype);
    EventList events(const Object* obj);
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;
};


LRESULT CALLBACK
EventDispatcher::dispatcher(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Object * obj = (Object *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    switch (message) {
        case WM_DESTROY:
            if (EventDispatcher::instance().objectRegisteredForEvent(obj, Event::Close)) {
                // obj->handleEvent(new Event(Event::Close));
            }
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

EventDispatcher&
EventDispatcher::instance() {
    static EventDispatcher inst;
    return inst;
}

EventDispatcher::EventDispatcher()
: ob2evMap{}
{}

void
EventDispatcher::registerObjectForEvent(const Object * obj, Event::Type etype) {
    ob2evMap[obj].push_back(etype);
}

EventDispatcher::EventList
EventDispatcher::events(const Object * obj) {
    return ob2evMap[obj];
}

const bool
EventDispatcher::objectRegisteredForEvent(Object * obj, Event::Type etype) {
    EventList evs = ob2evMap.find(obj)->second;
    if (std::count(evs.cbegin(), evs.cend(), etype) > 0) return true;
    return false;
}

#endif // PRISMEVENTDISPATCHER_H_
