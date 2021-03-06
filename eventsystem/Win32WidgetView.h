#ifndef WIN32WIDGETVIEW_H_
#define WIN32WIDGETVIEW_H_

#include "WidgetView.h"
#include <windows.h>
#include "Win32RunLoop.h"
#include "Object.h"
#include "WidgetModel.h"
#include "Event.h"
#include "CloseEvent.h"
#include "ResizeEvent.h"
#include "MouseEvent.h"

class Win32WidgetView : public WidgetView {
private:
    WNDCLASS            wndClass;
    HWND                m_hwnd;
    const TCHAR *       className; // eventually this should be the same as app name in global app object?
private:
    Win32WidgetView() = delete;
public:
    Win32WidgetView(WidgetModel * model, Object * observer)
    :   WidgetView(model, observer),
        className{TEXT("WindowClass")}
    {
        create();
    }

    virtual void
    create() override {
        initWindowClass();
        registerWindowClass();
        createWindow();
    }

    virtual void
    show() override {
        ShowWindow(m_hwnd, SW_SHOW);
    	UpdateWindow(m_hwnd);
    }

    virtual void
    update() override {
        SetWindowText(m_hwnd, TEXT(this->m_model->title().c_str()));
    }

    virtual void
    resize(const int width, const int height) override {
        RECT currentRect;
        GetWindowRect(hwnd(), &currentRect);
        int currentX = currentRect.left;
        int currentY = currentRect.top;

        RECT newRect = {currentX, currentY, currentX+width, currentY+height};
        DWORD styles = GetWindowLongPtr(hwnd(), GWL_STYLE);
        AdjustWindowRect(&newRect, styles, FALSE);
        SetWindowPos(hwnd(), HWND_TOP, newRect.left, newRect.top, newRect.right-newRect.left, newRect.bottom-newRect.top, SWP_SHOWWINDOW);
    }

    virtual HWND
    hwnd() const override {
        return m_hwnd;
    }
private:
    void
    initWindowClass() {
    	wndClass.style 			= CS_HREDRAW | CS_VREDRAW;
    	wndClass.lpfnWndProc 	= Win32RunLoop::WndProc;
    	wndClass.cbClsExtra 	= 0;
    	wndClass.cbWndExtra 	= 0;
    	wndClass.hInstance 		= GetModuleHandle(NULL);
    	wndClass.hIcon 			= LoadIcon(NULL, IDI_APPLICATION);
    	wndClass.hCursor 		= LoadCursor(NULL, IDC_ARROW);
    	wndClass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    	wndClass.lpszMenuName 	= NULL;
    	wndClass.lpszClassName 	= className;
    }

    void
    registerWindowClass() {
    	if (!RegisterClass(&wndClass))
    		MessageBox(NULL, TEXT("This program requires Windows NT"), className, MB_ICONERROR);
    }

    void
    createWindow() {
    	m_hwnd = CreateWindow(
    		className,
    		TEXT("Default window title"),
    		WS_OVERLAPPEDWINDOW, // creates a top level window, use WS_CHILDWINDOW otherwise
    		CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
    		NULL,
    		NULL,
    		GetModuleHandle(NULL),
    		NULL
    	);
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, LONG_PTR(this->observer()));
        // update model with initial width and height
        RECT rect;
        GetWindowRect(m_hwnd, &rect);
        this->m_model->setSize(rect.right-rect.left, rect.bottom-rect.top);
    }
};

#endif // WIN32WIDGETVIEW_H_
