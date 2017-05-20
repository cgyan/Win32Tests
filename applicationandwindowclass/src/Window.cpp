#include "Window.h"
#include "WindowImpl.h"

Window::Window()
:   impl{new WindowImpl}
{}

Window::~Window() {
    delete impl;
}

void
Window::show() {
    impl->show();
}

HWND
Window::hwnd() const {
    return impl->hwnd();
}
