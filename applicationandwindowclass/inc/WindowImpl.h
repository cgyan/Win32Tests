#ifndef WINDOWIMPL_H_
#define WINDOWIMPL_H_

#include <windows.h>
#include "AbstractObjectImpl.h"
#include "MessageRouter.h"
#include <iostream>

class WindowImpl : public AbstractObjectImpl {
private:
	WNDCLASS wndClass;
	HWND m_hwnd;
	const TCHAR * className;
public:
	WindowImpl();
	virtual ~WindowImpl();
	void show();
	HWND hwnd() const;
	virtual LRESULT CALLBACK handleMessage(HWND, UINT, WPARAM, LPARAM);
private:
	void initWindowClass();
	void registerWindowClass();
	void createWindow();
};

WindowImpl::WindowImpl()
:	className{TEXT("MainWindow")}
{
	initWindowClass();
	registerWindowClass();
	createWindow();
}

WindowImpl::~WindowImpl() {
	//
}

void
WindowImpl::initWindowClass() {
	wndClass.style 			= CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc 	= MessageRouter::MainMsgRouter;
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
WindowImpl::registerWindowClass() {
	if (!RegisterClass(&wndClass))
		MessageBox(NULL, TEXT("This program requires Windows NT"), className, MB_ICONERROR);
}

void
WindowImpl::createWindow() {
	m_hwnd = CreateWindow(
		className,
		TEXT("Creating a window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		this
	);
}

void
WindowImpl::show() {
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);
}

HWND
WindowImpl::hwnd() const {
	return m_hwnd;
}

LRESULT CALLBACK
WindowImpl::handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_COMMAND: {
			std::cout << map.size() << std::endl;
			std::map<HWND, AbstractObjectImpl *>::iterator it = map.find((HWND)lParam);
			if (it == map.end()) MessageBox(NULL, TEXT("Cannot find child control"), TEXT(""), MB_ICONERROR);
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif // WINDOWIMPL_H_
