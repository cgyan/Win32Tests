#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <windows.h>

class EventDispatcher {
public:
    static LRESULT CALLBACK dispatcher(HWND, UINT, WPARAM, LPARAM);
};

LRESULT CALLBACK
EventDispatcher::dispatcher(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_NCCREATE)
        SetWindowLongPtr(hwnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));


    if (Object * obj = (Object *)GetWindowLongPtr(hwnd, GWLP_USERDATA))
        return obj->handleMessage(hwnd, message, wParam, lParam);

    return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif // MESSAGEROUTER_H_
