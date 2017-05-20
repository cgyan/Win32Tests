#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style 			= CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc 	= WndProc;
	wndClass.cbClsExtra 	= 0;
	wndClass.cbWndExtra 	= 0;
	wndClass.hInstance 		= hInstance;
	wndClass.hIcon 			= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor 		= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName 	= NULL;
	wndClass.lpszClassName 	= szAppName;

	if (!RegisterClass(&wndClass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	int winX = CW_USEDEFAULT;
	int winY = CW_USEDEFAULT;
	int winW = 600;
	int winH = 400;

	hwnd = CreateWindow(szAppName,
						TEXT("The Hello Program"),
						WS_OVERLAPPEDWINDOW,
						winX, winY, winW, winH,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch(message) {
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rect);
			DrawText(hdc, TEXT("Hello, Windows!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			return 0;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
