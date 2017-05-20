#include <windows.h>
#include "Application.h"
#include "Window.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

	Application app;
	Window w;
	w.show();

	return app.run();

}
