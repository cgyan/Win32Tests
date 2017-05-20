#ifndef WIDGETIMPL_H_
#define WIDGETIMPL_H_

#include "WidgetModel.h"
#include "WidgetView.h"
#include "Win32WidgetView.h"
class Object;

class WidgetImpl {
protected:
    WidgetModel * model;
    WidgetView * view;
public:
    WidgetImpl() // called by subclass ctor
    :   model{nullptr},
        view{nullptr}
    {}

    WidgetImpl(Object * observer) // called by Widget ctor
    :   model{new WidgetModel},
        view{new Win32WidgetView(model, observer)}
        // view{new OSXWidgetView(model, observer)}
    {
        //
    }
public:
    virtual ~WidgetImpl() {
        delete view;
        delete model;
    }

    void
    setParent(Widget * parent) {
        view->attachToParentWidget(parent);
    }

    HWND
    hwnd() const {
        return view->hwnd();
    }

    void
    setTitle(const std::string& newTitle) {
        model->setTitle(newTitle);
        view->update();
    }

    void
    show() {
        view->show();
    }

    void
    resize(const int width, const int height) {
        model->setSize(width, height);
        view->update();
    }

    const int
    width() const {
        return model->width();
    }

    const int
    height() const {
        return model->height();
    }
};

#endif // WIDGETIMPL_H_
