#ifndef DERIVEDWIDGET_H_
#define DERIVEDWIDGET_H_

#include "Widget.h"
#include "CloseEvent.h"
#include "ResizeEvent.h"
#include <iostream>

class DerivedWidget : public Widget {
public:
    DerivedWidget() {
        //
    }
protected:
    virtual void
    onClose(CloseEvent * e) override {
        std::cout << "[DerivedWidget]::onClose event \n";
    }
};

#endif // DERIVEDWIDGET_H_
