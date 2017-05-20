#ifndef SIMPLEWINDOW_H_
#define SIMPLEWINDOW_H_

#include <windows.h>
#include "AbstractWindow.h"

class SimpleWindow : public AbstractWindow {
public:
	SimpleWindow(const TCHAR * windowName, const TCHAR * className);
	virtual LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void show();
};

SimpleWindow::SimpleWindow(const TCHAR * windowName, const TCHAR * className) {
	lpWindowName 	= windowName;
	lpClassName 	= className;
	hInstance 		= GetModuleHandle(NULL);
	dwStyle			= WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	x 				= CW_USEDEFAULT;
	y 				= CW_USEDEFAULT;
	width 			= CW_USEDEFAULT;
	height 			= CW_USEDEFAULT;
	dwExStyle 		= 0;
	hWndParent		= 0;
	hMenu 			= 0;
}

LRESULT CALLBACK
SimpleWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void
SimpleWindow::show() {
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

#endif // SIMPLEWINDOW_H_