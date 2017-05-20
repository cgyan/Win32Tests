#ifndef CLOSEEVENT_H_
#define CLOSEEVENT_H_

#include "Event.h"

class CloseEvent : public Event {
public:
    CloseEvent(Event::Type etype)
    : Event{etype}
    {}

    virtual ~CloseEvent() {}
};

#endif // CLOSEEVENT_H_
