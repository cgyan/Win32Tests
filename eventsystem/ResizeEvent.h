#ifndef RESIZEEVENT_H_
#define RESIZEEVENT_H_

#include "Event.h"

class ResizeEvent : public Event {
public:
    ResizeEvent(Event::Type etype, const int newWidth, const int newHeight)
    :   Event(etype),
        m_width(newWidth),
        m_height(newHeight)
    {}

    const int width() const {
        return m_width;
    }

    const int height() const {
        return m_height;
    }
private:
    int m_width;
    int m_height;
};

#endif // RESIZEEVENT_H_
