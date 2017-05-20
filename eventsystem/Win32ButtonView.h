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
    WNDPROC oldWndProc;
private:
    Win32ButtonView() = delete;
public:
    Win32ButtonView(ButtonModel * model, Object * observer);
    virtual void create() override;
    virtual void update() override;
    virtual void show() override;
    virtual HWND hwnd() const override;
    static LRESULT CALLBACK BtnWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
protected:
    virtual void attachToParentWidget(Widget * parent) override;
};

LRESULT CALLBACK
Win32ButtonView::BtnWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Win32ButtonView * bv = (Win32ButtonView *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    Event * ev = nullptr;

    switch (message) {
        case WM_SIZE:
            ev = new ResizeEvent(Event::Resize, LOWORD(lParam), HIWORD(lParam));
            bv->observer()->handleEvent(ev);
            delete ev;
            break;
        case WM_LBUTTONDOWN:
            ev = new MouseEvent(Event::MousePress);
            bv->observer()->handleEvent(ev);
            delete ev;
            break;
    }
    return CallWindowProc(bv->oldWndProc, hwnd, message, wParam, lParam);
}

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

    oldWndProc = (WNDPROC)SetWindowLongPtr(hbtn, GWLP_WNDPROC, (LONG_PTR)BtnWndProc);
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

HWND
Win32ButtonView::hwnd() const {
    return hbtn;
}

void
Win32ButtonView::attachToParentWidget(Widget * parent) {
    if (parent) {
        DWORD btnStyles = GetWindowLongPtr(hbtn, GWL_STYLE) & (WS_CHILD | WS_VISIBLE);
        SetWindowLongPtr(hbtn, GWL_STYLE, btnStyles);
        SetParent(hbtn, parent->hwnd());
        this->show();
    }
}

#endif // WIN32BUTTONVIEW_H_
