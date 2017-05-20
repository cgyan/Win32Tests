#include <windows.h>

HGDIOBJ curvePen = CreatePen(PS_SOLID, 10, RGB(255,0,0));
HGDIOBJ controlHandlePen = CreatePen(PS_DOT, 1, RGB(100,100,100));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("Bezier");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style 			= CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc 	= WndProc;
	wndClass.cbClsExtra 	= 0;
	wndClass.cbWndExtra 	= 0;
	wndClass.hInstance 		= hInstance;
	wndClass.hIcon 			= LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor	 	= LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground 	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName 	= NULL;
	wndClass.lpszClassName 	= szAppName;

	if (!RegisterClass(&wndClass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	int winX = CW_USEDEFAULT;
	int winY = CW_USEDEFAULT;
	int winW = CW_USEDEFAULT;
	int winH = CW_USEDEFAULT;

	hwnd = CreateWindow(szAppName,
						TEXT("Bezier Splines"),
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

void
DrawCurve(HDC hdc, POINT apt[]) {
	SelectObject(hdc, curvePen);
	PolyBezier(hdc, apt, 4);
}

void
DrawControlHandles(HDC hdc, POINT apt[]) {
	SelectObject(hdc, controlHandlePen);

	// left control handle
	MoveToEx(hdc, apt[0].x, apt[0].y, NULL);
	LineTo(hdc, apt[1].x, apt[1].y);
	Rectangle(hdc, apt[1].x - 5, apt[1].y - 5, apt[1].x + 5, apt[1].y + 5);

	// right control handle
	MoveToEx(hdc, apt[2].x, apt[2].y, NULL);
	LineTo(hdc, apt[3].x, apt[3].y);
	Rectangle(hdc, apt[2].x - 5, apt[2].y - 5, apt[2].x + 5, apt[2].y + 5);
	
}

void
DrawBezier(HDC hdc, POINT apt[]) {
	DrawControlHandles(hdc, apt);
	DrawCurve(hdc, apt);
}

LRESULT
handleSizeMsg(POINT apt[], LPARAM lParam) {
	int cxClient = LOWORD(lParam);
	int cyClient = HIWORD(lParam);

	apt[0].x = cxClient / 4;
	apt[0].y = cyClient / 2;

	apt[1].x = cxClient / 2;
	apt[1].y = cyClient / 4;

	apt[2].x = cxClient / 2;
	apt[2].y = 3 * cyClient / 4;

	apt[3].x = 3 * cxClient / 4;
	apt[3].y = cyClient / 2;

	return 0;
}

LRESULT
handleMouseMsg(HWND hwnd, POINT apt[], WPARAM wParam, LPARAM lParam) {
	if (wParam & MK_LBUTTON || wParam & MK_RBUTTON) {

		if (wParam & MK_LBUTTON) {
			apt[1].x = LOWORD(lParam);
			apt[1].y = HIWORD(lParam);
		}

		if (wParam & MK_RBUTTON) {
			apt[2].x = LOWORD(lParam);
			apt[2].y = HIWORD(lParam);
		}
		InvalidateRect(hwnd, NULL, TRUE); // posts a WM_PAINT msg into the queue
	}
	return 0;
}

LRESULT
handlePaintMsg(HWND hwnd, POINT apt[]) {
	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(hwnd, &ps);
	DrawBezier(hdc, apt);
	EndPaint(hwnd, &ps);

	return 0;
}

LRESULT
handleDestroyMsg() {
	DeleteObject(curvePen);
	DeleteObject(controlHandlePen);
	PostQuitMessage(0);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static POINT apt[4];

	switch(message) {
		case WM_SIZE:
			return handleSizeMsg(apt, lParam);
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MOUSEMOVE:
			return handleMouseMsg(hwnd, apt, wParam, lParam);
		case WM_PAINT:
			return handlePaintMsg(hwnd, apt);
		case WM_DESTROY:
			return handleDestroyMsg();
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);			
	}	
	
}