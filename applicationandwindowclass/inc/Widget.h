#ifndef WIDGET_H_
#define WIDGET_H_

#include "Object.h"

class WidgetImpl;

class Widget : public Object {
private:
    WidgetImpl * impl;
public:
    Widget();
    ~Widget();
};

#endif // WIDGET_H_
