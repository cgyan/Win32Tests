#include <windows.h>
#include "sysmets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("SysMets1");
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
						TEXT("Get System Metrics No. 1"),
						WS_OVERLAPPEDWINDOW,
						winX, winY, winW, winH,
						NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int cxChar, cxCaps, cyChar;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	TCHAR szBuffer[10];
	TEXTMETRIC tm;

	switch(message) {
		case WM_CREATE:
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth;
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			ReleaseDC(hwnd, hdc);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			for (i=0; i<NUMLINES; ++i) {
				TextOut(hdc, 0, cyChar * i, 
						sysmetrics[i].szLabel, 
						lstrlen(sysmetrics[i].szLabel));
				TextOut(hdc, 22 * cxCaps, cyChar * i, 
						sysmetrics[i].szDesc, 
						lstrlen(sysmetrics[i].szDesc));
				SetTextAlign(hdc, TA_RIGHT | TA_TOP);
				TextOut(hdc, 22 * cxCaps + 40 * cxChar, cyChar * i, szBuffer,
						wsprintf(szBuffer, TEXT("%5d"), 
							GetSystemMetrics(sysmetrics[i].iIndex)));
				SetTextAlign(hdc, TA_LEFT | TA_TOP);
			}
			EndPaint(hwnd, &ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}