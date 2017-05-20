#ifndef BUTTONIMPL_H_
#define BUTTONIMPL_H_

#include "WidgetImpl.h"
#include "ButtonModel.h"
#include "Win32ButtonView.h"

#define btn_model_cast(model) static_cast<ButtonModel *>(model)

class ButtonImpl : public WidgetImpl {
private:
    ButtonImpl() = delete;
public:
    ButtonImpl(Object * observer);
    ~ButtonImpl();
};

ButtonImpl::ButtonImpl(Object * observer)
:   WidgetImpl{}
{
    this->model = new ButtonModel;
    this->view = new Win32ButtonView(btn_model_cast(model), observer);
}

ButtonImpl::~ButtonImpl() {
    // check that ButtonModel and ButtonView are destroyed when Widget destructor is called
}



#endif // BUTTONIMPL_H_
