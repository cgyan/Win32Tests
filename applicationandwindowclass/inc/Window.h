#ifndef WINDOW_H_
#define WINDOW_H_

#include <windows.h>
#include "Widget.h"

class WindowImpl;

class Window : public Widget {
private:
    WindowImpl * impl;
public:
    Window();
    ~Window();
    void show();
    HWND hwnd() const;
};

#endif // WINDOW_H_
