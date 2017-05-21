#ifndef WIN32BUTTONVIEW_H_
#define WIN32BUTTONVIEW_H_

#include <windows.h>
#include "WidgetView.h"
#include "ResizeEvent.h"
#include <iostream>
#include <cassert>


class Win32ButtonView : public WidgetView {
private:
    HWND hbtn;
private:
    Win32ButtonView() = delete;
public:
    Win32ButtonView(ButtonModel * model, Object * observer);
    virtual void create() override;
    virtual void update() override;
    virtual void show() override;
    virtual void resize(const int width, const int height) override;
    virtual HWND hwnd() const override;
protected:
    virtual void attachToParentWidget(Widget * parent) override;
};

Win32ButtonView::Win32ButtonView(ButtonModel * model, Object * observer)
:   WidgetView{model, observer}
{
    create();
}

void
Win32ButtonView::create() {
    hbtn = CreateWindow(
        TEXT("BUTTON"),
        TEXT("Placeholder"),
        BS_DEFPUSHBUTTON,
        10, 10,
        100, 35,
        NULL, // no parent set initially
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    SetWindowLongPtr(hbtn, GWLP_USERDATA, LONG_PTR(this->observer()));
}

void
Win32ButtonView::update() {
    SetWindowText(hbtn, TEXT(this->m_model->title().c_str()));
}

void
Win32ButtonView::show() {
    ShowWindow(hbtn, SW_SHOW);
}

void
Win32ButtonView::resize(const int width, const int height) {
    RECT rect;
    GetWindowRect(hwnd(), &rect);
    SetWindowPos(hwnd(), HWND_TOP, rect.left, rect.top, width, height, SWP_SHOWWINDOW);
}

HWND
Win32ButtonView::hwnd() const {
    return hbtn;
}

void
Win32ButtonView::attachToParentWidget(Widget * parent) {
    assert(parent);
    if (parent) {
        DWORD btnStyles = GetWindowLongPtr(hbtn, GWL_STYLE) & (WS_CHILD | WS_VISIBLE);
        SetWindowLongPtr(hbtn, GWL_STYLE, btnStyles);
        SetParent(hbtn, parent->hwnd());
        this->show();
    }
}

#endif // WIN32BUTTONVIEW_H_
