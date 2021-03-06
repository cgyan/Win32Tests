#include "Widget.h"
#include "WidgetImpl.h"
#include "Event.h"
#include "CloseEvent.h"
#include "ResizeEvent.h"
#include "MouseEvent.h"
#include <windows.h>
//=============================================================================================
// Widget
//=============================================================================================
Widget::Widget(Widget * parent)
:   Object(parent),
    impl{new WidgetImpl(this)}
{
    if (parent) impl->setParent(parent);
}

Widget::Widget(WidgetImpl * impl, Widget * parent)
:   Object(parent),
    impl{impl}
{
    if (parent) impl->setParent(parent);
}

Widget::~Widget() {
    delete impl;
}

HWND
Widget::hwnd() const {
    return impl->hwnd();
}

void
Widget::setParent(Widget * parent) {
    assert(parent);
    Object::setParent(parent);
    impl->setParent(parent);
}

void
Widget::setTitle(const std::string& newTitle) {
    impl->setTitle(newTitle);
}

void
Widget::show() {
    impl->show();
}

void
Widget::resize(const int width, const int height) {
    impl->resize(width, height);
}

const int
Widget::width() const {
    return impl->width();
}

const int Widget::height() const {
    return impl->height();
}

void
Widget::handleEvent(Event * e) {
    switch (e->type()) {
        case Event::Close:
            onClose(static_cast<CloseEvent *>(e));
            break;
        case Event::Resize:
            onResize(static_cast<ResizeEvent *>(e));
            break;
        case Event::MousePress:
            onMousePress(static_cast<MouseEvent *>(e));
            break;
    }
}

void
Widget::onClose(CloseEvent * event) {
    std::cout << "[Widget]::onClose event \n";
}

void
Widget::onResize(ResizeEvent * event) {
    impl->onResize(event->width(), event->height());
    std::cout << "Widget::onResize event " << event->width() << " " << event->height() << std::endl;
    std::cout << "Widget::onResize model " << this->width() << " " << this->height() << std::endl;
}

void
Widget::onMousePress(MouseEvent * event) {
    //
}
