#ifndef ABSTRACTWINDOW_H_
#define ABSTRACTWINDOW_H_

#include <windows.h>

class AbstractWindow {
public:
    virtual LRESULT CALLBACK handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

class Window {
private:
    struct WindowImpl;
    WindowImpl * impl;
public:
    Window();
    ~Window();
};

Window::Window()
:   impl{new WindowImpl}
{}

Window::~Window() {
    delete impl;
}

#endif // ABSTRACTWINDOW_H_
