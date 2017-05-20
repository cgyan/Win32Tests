#ifndef ABSTRACTOBJECTIMPL_H_
#define ABSTRACTOBJECTIMPL_H_

#include <windows.h>
#include <map>

class AbstractObjectImpl {
public:
    std::map<HWND, AbstractObjectImpl *> map;
public:
    virtual ~AbstractObjectImpl() {}
    virtual LRESULT CALLBACK handleMessage(HWND, UINT, WPARAM, LPARAM) = 0;
};

#endif // ABSTRACTOBJECTIMPL_H_
