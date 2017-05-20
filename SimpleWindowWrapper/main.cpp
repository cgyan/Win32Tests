#include "AbstractWindow.h"
#include "SimpleWindowClass.h"
#include "SimpleWindow.h"

int WINAPI 
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	SimpleWindowClass wndClass(TEXT("My window class"));
	wndClass.registerWindow();

	SimpleWindow wnd(TEXT("Window title"), wndClass.className());
	wnd.create();
	wnd.show();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

