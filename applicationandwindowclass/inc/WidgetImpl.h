#ifndef WIDGETIMPL_H_
#define WIDGETIMPL_H_

#include <windows.h>
#include "AbstractObjectImpl.h"

class WidgetImpl : public AbstractObjectImpl {
public:
    virtual ~WidgetImpl() {}
    virtual LRESULT CALLBACK handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
        return DefWindowProc(hwnd, message, wParam, lParam);
    };
};



#endif // WIDGETIMPL_H_
