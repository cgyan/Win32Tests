#ifndef EVENT_H_
#define EVENT_H_

class Event {
public:
    enum Type { Close, Resize, MousePress };
private:
    Type m_type;
public:
    Event(Event::Type etype)
    :   m_type{etype}
    {}

    virtual ~Event() {}

    Type
    type() const {
        return m_type;
    }
};

#endif // EVENT_H_
