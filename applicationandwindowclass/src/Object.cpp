#include "Object.h"
#include "ObjectImpl.h"

Object::Object()
:   impl{new ObjectImpl}
{}

Object::~Object() {
    delete impl;
}
