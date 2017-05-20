#include "Button.h"
#include "ButtonImpl.h"
#include "Window.h"

Button::Button(Window* parentWindow)
:   impl{new ButtonImpl(parentWindow)}
{}

Button::~Button() {
    delete impl;
}

void Button::show() {
    impl->show();
}
