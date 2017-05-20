#include "Object.h"

Object::Object(Object * parent) {
    setParent(parent);
}

Object::~Object() {
    //
}

void
Object::handleEvent(Event * e) {
    // do-nothing implementation
    std::cout << "Object::handleEvent \n";
}

void
Object::setParent(Object * parent) {
    this->m_parent = parent; // 'parent' might be null
    if (parent != nullptr)
        addThisObjectToParentsChildren(parent);
}

void
Object::addThisObjectToParentsChildren(Object * parent) {
    assert(parent != nullptr);
    parent->m_children.push_back(this);
}

Object *
Object::parent() const {
    return m_parent;
}

ObjectList
Object::children() const {
    return m_children;
}
