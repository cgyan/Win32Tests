#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

#include "Event.h"

class MouseEvent : public Event {
public:
    MouseEvent(Event::Type etype)
    :   Event(etype)
    {}
};



#endif // MOUSEEVENT_H_
