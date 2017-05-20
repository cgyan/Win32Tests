#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("AltWind");
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
						TEXT("Alternate and Winding fill modes"),
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
	static POINT aptFigure[10] = { 	10,70,  50,70,  50,10,  90,10,  90,50,
									30,50,  30,90,  70,90,  70,30,  10,30 };
	static int cxClient;
	static int cyClient;
	HDC hdc;
	PAINTSTRUCT ps;
	POINT apt[10];

	switch (message) {
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			return 0;
		case WM_PAINT:
			{
				hdc = BeginPaint(hwnd, &ps);
				COLORREF fillColor = RGB(0,255,0);
				COLORREF borderColor = RGB(255, 0, 0);
				// HBRUSH newBrush = CreateHatchBrush(HS_DIAGCROSS, fillColor);
				HBRUSH newBrush = CreateSolidBrush(fillColor);
				HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
				HPEN newPen = CreatePen(PS_SOLID, 4, borderColor);
				HPEN oldPen = (HPEN)SelectObject(hdc, newPen);
				
				for (int i=0; i<10; ++i) {
					apt[i].x = cxClient * aptFigure[i].x / 200;
					apt[i].y = cyClient * aptFigure[i].y / 100;
				}

				SetPolyFillMode(hdc, ALTERNATE);
				Polygon(hdc, apt, 10);

				for (int i=0; i<10; ++i) {
					apt[i].x += cxClient / 2;
				}

				SetPolyFillMode(hdc, WINDING);
				Polygon(hdc, apt, 10);

				DeleteObject(newBrush);
				DeleteObject(newPen);
				SelectObject(hdc, oldBrush);
				SelectObject(hdc, oldPen);
				EndPaint(hwnd, &ps);
				return 0;
			}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
}