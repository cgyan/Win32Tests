#ifndef OBJECT_H_
#define OBJECT_H_

class ObjectImpl;

class Object {
private:
    ObjectImpl * impl;
public:
    Object();
    ~Object();
};

#endif // OBJECT_H_
