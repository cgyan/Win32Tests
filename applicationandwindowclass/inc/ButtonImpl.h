#ifndef BUTTONIMPL_H_
#define BUTTONIMPL_H_

#include <windows.h>
#include "Window.h"
#include "AbstractObjectImpl.h"

class ButtonImpl : public AbstractObjectImpl {
private:
    HWND hwnd;
public:
    ButtonImpl(Window * parentWindow = 0);
    virtual ~ButtonImpl();
    void show();
    virtual LRESULT CALLBACK handleMessage(HWND, UINT, WPARAM, LPARAM);
};

ButtonImpl::ButtonImpl(Window * parentWindow) {
    hwnd = CreateWindow(
        TEXT("BUTTON"),
        TEXT("Click me!"),
        WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        parentWindow->hwnd(),
        (HMENU)111,
        GetModuleHandle(NULL),
        this
    );

    map.insert(std::pair<HWND, AbstractObjectImpl *>(hwnd, this));
}

ButtonImpl::~ButtonImpl() {
    //
}

void
ButtonImpl::show() {
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK
ButtonImpl::handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_COMMAND:
            MessageBox(NULL, TEXT("button was clicked!"), TEXT(""), MB_ICONERROR);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif // BUTTONIMPL_H_
