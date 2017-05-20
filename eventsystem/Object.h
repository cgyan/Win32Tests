#ifndef OBJECT_H_
#define OBJECT_H_

#include <list>
#include <iostream>
#include <cassert>
class Event;
class Object;
using ObjectList = std::list<Object *>;

class Object {
private:
    ObjectList      m_children;
    Object *        m_parent{nullptr};
public:
                    Object(Object * parent);
    virtual         ~Object();

    virtual void    handleEvent(Event * e);
    void            setParent(Object * parent);
    Object *        parent() const;
    ObjectList      children() const;
private:
    void            addThisObjectToParentsChildren(Object * parent);
};



#endif // OBJECT_H_
