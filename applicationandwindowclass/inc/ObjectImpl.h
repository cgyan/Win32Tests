#ifndef OBJECTIMPL_H_
#define OBJECTIMPL_H_

#include "AbstractObjectImpl.h"

class ObjectImpl : public AbstractObjectImpl {
public:
    virtual ~ObjectImpl() {}
    virtual LRESULT CALLBACK handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

LRESULT CALLBACK
ObjectImpl::handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif // OBJECTIMPL_H_
