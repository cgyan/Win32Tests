#include <windows.h>
#include <algorithm>
#include "sysmets.h"

static int cxChar, cxCaps, cyChar, cxClient, cyClient, iMaxWidth;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT handleCreateMsg(HWND, UINT);
LRESULT handleSizeMsg(HWND hwnd, LPARAM lParam, WPARAM wParam);
LRESULT handleVertScrollMsg(HWND hwnd, WPARAM wParam);
void setVerticalScrollBarRangeAndPageSize(HWND);
void setHorizontalScrollBarRangeAndPageSize(HWND);
LRESULT handleHorzScrollMsg(HWND hwnd, WPARAM wParam);
LRESULT handlePaintMsg(HWND hwnd);
LRESULT handleDestroyMsg();
void retrieveTextMetrics(HDC hdc);
void paintTextCols(HDC hdc, PAINTSTRUCT ps, int iVertPos, int iHorzPos);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("SysMets3");
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
						TEXT("Get system metrics No.3"),
						WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
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
	switch (message) {
		case WM_CREATE:
			return handleCreateMsg(hwnd, message);
		case WM_SIZE:
			return handleSizeMsg(hwnd, lParam, wParam);
		case WM_VSCROLL:
			return handleVertScrollMsg(hwnd, wParam);
		case WM_HSCROLL:
			return handleHorzScrollMsg(hwnd, wParam);
		case WM_PAINT:
			return handlePaintMsg(hwnd);
		case WM_DESTROY:
			return handleDestroyMsg();
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
}

LRESULT handleCreateMsg(HWND hwnd, UINT message) {
	HDC hdc;
	hdc = GetDC(hwnd);
	retrieveTextMetrics(hdc);
	ReleaseDC(hwnd, hdc);
	iMaxWidth = 40 * cxChar + 22 * cxCaps;
	return 0;
}

void retrieveTextMetrics(HDC hdc) {
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	cxChar = tm.tmAveCharWidth;
	cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
	cyChar = tm.tmHeight + tm.tmExternalLeading;
}

LRESULT handleSizeMsg(HWND hwnd, LPARAM lParam, WPARAM wParam) {
	cxClient = LOWORD(lParam);
	cyClient = HIWORD(lParam);
	setVerticalScrollBarRangeAndPageSize(hwnd);
	setHorizontalScrollBarRangeAndPageSize(hwnd);
	return 0;
}

void setVerticalScrollBarRangeAndPageSize(HWND hwnd) {
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = NUMLINES - 1;
	si.nPage = cyClient / cyChar;
	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
}

void setHorizontalScrollBarRangeAndPageSize(HWND hwnd) {
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = 2 + iMaxWidth / cxChar;
	si.nPage = cxClient / cxChar;
	SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
}

LRESULT handleVertScrollMsg(HWND hwnd, WPARAM wParam) {
	SCROLLINFO si;
	int iVertPos = 0;
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	GetScrollInfo(hwnd, SB_VERT, &si);
	iVertPos = si.nPos;
	switch (LOWORD(wParam)) {
		case SB_TOP:
			si.nPos = si.nMin;
			break;
		case SB_BOTTOM:
			si.nPos = si.nMax;
			break;
		case SB_LINEUP:
			si.nPos -= 1;
			break;
		case SB_LINEDOWN:
			si.nPos += 1;
			break;
		case SB_PAGEUP:
			si.nPos -= si.nPage;
			break;
		case SB_PAGEDOWN:
			si.nPos += si.nPage;
			break;
		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;
		default:
			break;
	}
	si.fMask = SIF_POS;
	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
	GetScrollInfo(hwnd, SB_VERT, &si);
	if (si.nPos != iVertPos) {
		ScrollWindow(hwnd, 0, cyChar * (iVertPos - si.nPos), NULL, NULL);
		UpdateWindow(hwnd);
	}
	return 0;
}

LRESULT handleHorzScrollMsg(HWND hwnd, WPARAM wParam) {
	SCROLLINFO si;
	int iHorzPos;
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	GetScrollInfo(hwnd, SB_HORZ, &si);
	iHorzPos = si.nPos;
	switch (LOWORD(wParam)) {
		case SB_LINELEFT:
			si.nPos -= 1;
			break;
		case SB_LINERIGHT:
			si.nPos += 1;
			break;
		case SB_PAGELEFT:
			si.nPos -= si.nPage;
			break;
		case SB_PAGERIGHT:
			si.nPos += si.nPage;
			break;
		case SB_THUMBPOSITION:
			si.nPos = si.nTrackPos;
			break;
		default:
			break;
	}
	si.fMask = SIF_POS;
	SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
	GetScrollInfo(hwnd, SB_HORZ, &si);
	if (si.nPos != iHorzPos) {
		ScrollWindow(hwnd, cxChar * (iHorzPos - si.nPos), 0, NULL, NULL);
	}
	return 0;
}

LRESULT handlePaintMsg(HWND hwnd) {
	HDC hdc;
	SCROLLINFO si;
	PAINTSTRUCT ps;
	int iVertPos, iHorzPos;

	hdc = BeginPaint(hwnd, &ps);

	si.cbSize = sizeof(si);
	si.fMask = SIF_POS;
	GetScrollInfo(hwnd, SB_VERT, &si);
	iVertPos = si.nPos;
	GetScrollInfo(hwnd, SB_HORZ, &si);
	iHorzPos = si.nPos;
	
	paintTextCols(hdc, ps, iVertPos, iHorzPos);

	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT handleDestroyMsg() {
	PostQuitMessage(0);
	return 0;			
}

void paintTextCols(HDC hdc, PAINTSTRUCT ps, int iVertPos, int iHorzPos) {
	int iPaintBeg = std::max(0, static_cast<int>((iVertPos + ps.rcPaint.top / cyChar)));
	int iPaintEnd = std::min(NUMLINES - 1, static_cast<int>(iVertPos + ps.rcPaint.bottom / cyChar));
	int x, y;
	TCHAR szBuffer[10];

	for (int i = iPaintBeg; i <= iPaintEnd; ++i) {
		x = cxChar * (1 - iHorzPos);
		y = cyChar * (i - iVertPos);
		TextOut(hdc, x, y, 
				sysmetrics[i].szLabel, 
				lstrlen(sysmetrics[i].szLabel));
		TextOut(hdc, x + 22 * cxCaps, y, 
				sysmetrics[i].szDesc, 
				lstrlen(sysmetrics[i].szDesc));
		SetTextAlign(hdc, TA_RIGHT | TA_TOP);
		TextOut(hdc, x + 22 * cxCaps + 40 * cxChar, y, szBuffer,
				wsprintf(szBuffer, TEXT("%5d"), 
					GetSystemMetrics(sysmetrics[i].iIndex)));
		SetTextAlign(hdc, TA_LEFT | TA_TOP);
	}
}