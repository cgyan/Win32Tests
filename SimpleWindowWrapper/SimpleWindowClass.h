#ifndef SIMPLEWINDOWCLASS_H_
#define SIMPLEWINDOWCLASS_H_

#include <windows.h>

class SimpleWindowClass {
private:
	WNDCLASSEX wndClassEx{0};
public:
	SimpleWindowClass(const TCHAR * className);
	const bool registerWindow();
	const TCHAR * className() const;
};

SimpleWindowClass::SimpleWindowClass(const TCHAR * className) {
	wndClassEx.cbSize 			= sizeof(wndClassEx);
	wndClassEx.style 			= CS_HREDRAW | CS_VREDRAW;
	wndClassEx.lpfnWndProc 		= AbstractWindow::msgRouter;
	wndClassEx.cbClsExtra 		= 0;
	wndClassEx.cbWndExtra 		= 0;
	wndClassEx.hInstance 		= GetModuleHandle(NULL);
	wndClassEx.hIcon 			= LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hCursor 			= LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hbrBackground 	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClassEx.lpszMenuName 	= NULL;
	wndClassEx.lpszClassName 	= className;
	wndClassEx.hIconSm 			= LoadIcon(NULL, IDI_APPLICATION);
}

const bool
SimpleWindowClass::registerWindow() {
	if (RegisterClassEx(&wndClassEx)) return true;
	return false;
}

const TCHAR *
SimpleWindowClass::className() const {
	return wndClassEx.lpszClassName;
}

#endif /* SIMPLEWINDOWCLASS_H_ */
