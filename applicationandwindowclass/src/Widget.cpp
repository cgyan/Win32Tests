#include "Widget.h"
#include "WidgetImpl.h"

Widget::Widget()
: impl{new WidgetImpl}
{}

Widget::~Widget() {
    delete impl;
}
