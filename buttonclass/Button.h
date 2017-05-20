#ifndef PRISM_BUTTON_H_
#define PRISM_BUTTON_H_

#include <windows.h>
#include <map>

class Button;

std::map<HWND, Button*> map;

class Button {
private:
    HWND hwnd;
public:
    Button(HWND parentWindow = 0);
    void show();
    void onClick();
};

Button::Button(HWND parentWindow)
:   hwnd{}
{
    hwnd = CreateWindow(
        TEXT("BUTTON"),
        TEXT("Click me!"),
        WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        parentWindow,
        (HMENU)111,
        GetModuleHandle(NULL),
        NULL
    );

    map.insert(std::pair<HWND, Button*>(hwnd, this));
}

void Button::show() {
    ShowWindow(hwnd, SW_SHOW);
}

void
Button::onClick() {
    MessageBox(NULL, TEXT("Button was clicked"), TEXT(""), MB_ICONERROR);
}

#endif //PRISM_BUTTON_H_
