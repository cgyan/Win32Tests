#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

class Event;
class Object;

class EventQueue {
public:
    virtual ~EventQueue() {}
    virtual Event * nextEvent() = 0;
    static Event currentEvent;
    static Object * currentReceiver;
};

#endif // EVENTQUEUE_H_
