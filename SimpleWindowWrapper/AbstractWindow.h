#ifndef ABSTRACTWINDOW_H_
#define ABSTRACTWINDOW_H_

#include <windows.h>

class AbstractWindow {
protected:
	HWND hwnd;
	DWORD dwExStyle;
	LPCTSTR lpClassName;
	LPCTSTR lpWindowName;
	DWORD dwStyle;
	int x;
	int y;
	int width;
	int height;
	HWND hWndParent;
	HMENU hMenu;
	HINSTANCE hInstance;
public:
	virtual LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM) = 0;

	AbstractWindow();
	virtual ~AbstractWindow();
	static LRESULT CALLBACK msgRouter(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual const bool create();
};

AbstractWindow::AbstractWindow()
: 	hwnd{}, 
	dwExStyle{}, 
	lpClassName{}, 
	lpWindowName{}, 
	dwStyle{},
  	x{CW_USEDEFAULT}, 
  	y{CW_USEDEFAULT}, 
  	width{CW_USEDEFAULT}, 
  	height{CW_USEDEFAULT},
  	hWndParent{NULL}, 
  	hMenu{NULL}, 
  	hInstance{}
{}

AbstractWindow::~AbstractWindow() {

}

LRESULT CALLBACK 
AbstractWindow::msgRouter(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	AbstractWindow * wnd = 0;

	if (message == WM_NCCREATE) 
		SetWindowLongPtr(hwnd, GWLP_USERDATA, intptr_t((LPCREATESTRUCT(lParam))->lpCreateParams));
	
	wnd = (AbstractWindow*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	
	if (wnd) return wnd->WndProc(hwnd, message, wParam, lParam);
	else return DefWindowProc(hwnd, message, wParam, lParam);
}

const bool
AbstractWindow::create() {
	hwnd = CreateWindowEx(	dwExStyle, 
							lpClassName, 
							lpWindowName, 
							dwStyle,
							x, 
							y, 
							width, 
							height,
							hWndParent, 
							hMenu, 
							hInstance, 
							this);

	if (!hwnd) return false;
	return true;
}

#endif // ABSTRACTWINDOW_H_