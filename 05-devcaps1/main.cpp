#include <windows.h>
#include "devcaps.h"

static int cxChar, cxCaps, cyChar;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT handleCreateMsg(HWND);
LRESULT handlePaintMsg(HWND);
LRESULT handleDestroyMsg();
void drawText(HDC);
void drawLabel(HDC, int);
void drawDescription(HDC, int);
void drawValue(HDC, int);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("DevCaps1");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szAppName;

	if (!RegisterClass(&wndClass)) {
		MessageBox(NULL, TEXT("This program requires Windows NT"), szAppName, MB_ICONERROR);
		return 0;
	}

	int winX = CW_USEDEFAULT;
	int winY = CW_USEDEFAULT;
	int winW = CW_USEDEFAULT;
	int winH = CW_USEDEFAULT;

	hwnd = CreateWindow(szAppName,
						TEXT("Device Capabilities No.1"),
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

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
		case WM_CREATE:		return handleCreateMsg(hwnd);
		case WM_PAINT:		return handlePaintMsg(hwnd);
		case WM_DESTROY:	return handleDestroyMsg();
		default:			return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

LRESULT handleCreateMsg(HWND hwnd) {
	HDC hdc = GetDC(hwnd);
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	cxChar = tm.tmAveCharWidth;
	cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
	cyChar = tm.tmHeight + tm.tmExternalLeading;
	ReleaseDC(hwnd, hdc);
	return 0;
}

LRESULT handlePaintMsg(HWND hwnd) {
	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(hwnd, &ps);
	drawText(hdc);
	EndPaint(hwnd, &ps);
	return 0;
}

void drawText(HDC hdc) {
	for (int i = 0; i < NUMLINES; ++i) {
		drawLabel(hdc, i);
		drawDescription(hdc, i);
		SetTextAlign(hdc, TA_RIGHT | TA_TOP);
		drawValue(hdc, i);
		SetTextAlign(hdc, TA_LEFT | TA_TOP);
	}
}

void drawLabel(HDC hdc, int i) {
	// TextOut(handle to device context, x pos, y pos, ptr to string, string length)
	int x = 5;
	int y = cyChar * i;
	TCHAR const * pstr = devcaps[i].szLabel;
	int stringLength = lstrlen(devcaps[i].szLabel);
	TextOut(hdc, x, y, pstr, stringLength);
}

void drawDescription(HDC hdc, int i) {
	int x = 14 * cxCaps;
	int y = cyChar * i;
	TCHAR const * pstr = devcaps[i].szDesc;
	int stringLength = lstrlen(devcaps[i].szDesc); 
	TextOut(hdc, x, y, pstr, stringLength);
}

void drawValue(HDC hdc, int i) {
	int x = 14 * cxCaps + 35 * cxChar;
	int y = cyChar * i;
	TCHAR szBuffer[10];
	int stringLength = wsprintf(szBuffer, TEXT("%5d"), GetDeviceCaps(hdc, devcaps[i].iIndex));
	TextOut(hdc, x, y, szBuffer, stringLength);
}

LRESULT handleDestroyMsg() {
	PostQuitMessage(0);
	return 0;		
}