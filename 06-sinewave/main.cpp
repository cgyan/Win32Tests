#include <windows.h>
#include <math.h>

#define NUMPOINTS 1000
#define TWOPI (2 * 3.14159) 

static int cxClient, cyClient;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT handleSizeMsg(LPARAM);
LRESULT handlePaintMsg(HWND);
LRESULT handleDestroyMsg();
void drawHorzLine(HDC);
void calculateWavePoints(POINT *);
void drawWavePoints(HDC, POINT *);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("SineWave");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance; // or could use GetModuleHandle(NULL);
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
						TEXT("Sine Wave using Polyline"),
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
	switch (message) {
		case WM_SIZE:
			return handleSizeMsg(lParam);
		case WM_PAINT:
			return handlePaintMsg(hwnd);
		case WM_DESTROY:
			return handleDestroyMsg();
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

LRESULT
handleSizeMsg(LPARAM lParam) {
	cxClient = LOWORD(lParam);
	cyClient = HIWORD(lParam);
	return 0;
}

LRESULT
handlePaintMsg(HWND hwnd) {
	HDC hdc;
	PAINTSTRUCT ps;
	POINT apt[NUMPOINTS];

	hdc = BeginPaint(hwnd, &ps);

	drawHorzLine(hdc);
	calculateWavePoints(apt);
	drawWavePoints(hdc, apt);

	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT
handleDestroyMsg() {
	PostQuitMessage(0);
	return 0;		
}

void
drawHorzLine(HDC hdc) {
	MoveToEx(hdc, 0, cyClient / 2, NULL);
	LineTo(hdc, cxClient, cyClient / 2);	
}

void
calculateWavePoints(POINT * apt) {
	for (int i=0; i<NUMPOINTS; ++i) {
		apt[i].x = i * cxClient / NUMPOINTS;
		apt[i].y = (int)(cyClient / 2 * (1 - std::sin(TWOPI * i / NUMPOINTS)));
	}
}

void
drawWavePoints(HDC hdc, POINT * apt) {
	PolylineTo(hdc, apt, NUMPOINTS);
}