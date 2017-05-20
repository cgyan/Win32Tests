#include <windows.h>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawRectangle(HWND);

int cxClient, cyClient;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("RandRect");
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
						TEXT("Randow Rectangles"),
						WS_OVERLAPPEDWINDOW,
						winX, winY, winW, winH,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

    while (TRUE) {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break ;

            TranslateMessage (&msg) ;
            DispatchMessage (&msg) ;
        }
        else
            DrawRectangle (hwnd) ;
    }
    return msg.wParam ;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

void DrawRectangle(HWND hwnd) {
    HBRUSH hbrush;
    HDC hdc;
    RECT rect;

    if (cxClient == 0 || cyClient == 0)
        return;

    SetRect(&rect, rand() % cxClient, rand() % cyClient,
                rand() % cxClient, rand() % cyClient);

    hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
    hdc = GetDC(hwnd);

    FillRect(hdc, &rect, hbrush);
    ReleaseDC(hwnd, hdc);
    DeleteObject(hbrush);
}
