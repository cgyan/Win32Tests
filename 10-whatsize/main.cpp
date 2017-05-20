#include <windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("WhatSize");
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
	int winW = 600;
	int winH = 400;

	hwnd = CreateWindow(szAppName,
						TEXT("What size is the window?"),
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

void show(HWND hwnd, HDC hdc, int xText, int yText, int iMapMode, const TCHAR* szMapMode) {
    TCHAR szBuffer[60];
    RECT rect;
    SaveDC(hdc);
    SetMapMode(hdc, iMapMode);
    GetClientRect(hwnd, &rect);
    DPtoLP(hdc, (PPOINT)&rect, 2);
    RestoreDC(hdc, -1);
    TextOut(hdc, xText, yText, szBuffer,
        wsprintf(szBuffer, TEXT("%-20s %7d %7d %7d %7d"), szMapMode,
        rect.left, rect.right, rect.top, rect.bottom));
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static TCHAR szHeading[] = TEXT("Mapping Mode            Left   Right     Top  Bottom");
    static TCHAR szUndLine[] = TEXT("------------            ----   -----     ---  ------");
    static int cxChar, cyChar;
    HDC hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch (message) {
        case WM_CREATE:
            hdc = GetDC(hwnd);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cyChar = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hwnd, hdc);
            return 0;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

            SetMapMode(hdc, MM_ANISOTROPIC);
            SetWindowExtEx(hdc, 1, 1, NULL);
            SetViewportExtEx(hdc, cxChar, cyChar, NULL);

            TextOut(hdc, 1, 1, szHeading, lstrlen(szHeading));
            TextOut(hdc, 1, 2, szUndLine, lstrlen(szUndLine));

            show(hwnd, hdc, 1, 3, MM_TEXT, TEXT("TEXT (pixels)"));
            show(hwnd, hdc, 1, 4, MM_LOMETRIC, TEXT("LOMETRIC (.1 mm)"));
            show(hwnd, hdc, 1, 5, MM_HIMETRIC, TEXT("HIMETRIC (.01 mm)"));
            show(hwnd, hdc, 1, 6, MM_LOENGLISH, TEXT("LOENGLISH (.01 in)"));
            show(hwnd, hdc, 1, 7, MM_HIENGLISH, TEXT("HIENGLISH (.001 in)"));
            show(hwnd, hdc, 1, 8, MM_TWIPS, TEXT("TWIPS (1/1440 in)"));

            EndPaint(hwnd, &ps);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
}
