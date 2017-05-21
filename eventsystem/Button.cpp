#include "Button.h"
#include "ButtonImpl.h"
#include <cassert>
#include <iostream>

Button::Button(Widget * parent)
:   Widget(new ButtonImpl(this), parent)
{

}

Button::~Button() {
    //
}

void
Button::setText(const std::string& text) {
    impl->setTitle(text);
}

void
Button::onResize(ResizeEvent * e) {
    impl->onResize(e->width(), e->height());
}

void
Button::onMousePress(MouseEvent * e) {
    std::cout << "Btn pressed \n";
}
