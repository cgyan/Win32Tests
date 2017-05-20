#include <windows.h>

struct {
    int iStyle;
    const TCHAR * szText;
}
button[] = {
    BS_PUSHBUTTON,      TEXT("PUSHBUTTON"),
    BS_DEFPUSHBUTTON,   TEXT("DEFPUSHBUTTON"),
    BS_CHECKBOX,        TEXT("CHECKBOX"),
    BS_AUTOCHECKBOX,    TEXT("AUTOCHECKBOX"),
    BS_RADIOBUTTON,     TEXT("RADIOBUTTON"),
    BS_3STATE,          TEXT("3STATE"),
    BS_AUTO3STATE,      TEXT("AUTO3STATE"),
    BS_GROUPBOX,        TEXT("GROUPBOX"),
    BS_AUTORADIOBUTTON, TEXT("AUTORADIOBUTTON"),
    BS_OWNERDRAW,       TEXT("OWNERDRAW")
};

#define NUM (sizeof button / sizeof button[0])

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR szCmdLine, int iCmdShow) {
    static TCHAR szAppName[] = TEXT("BtnLook");
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
        MessageBox(NULL, TEXT("Could not register window"), szAppName, MB_ICONERROR);
    }

    hwnd = CreateWindow(szAppName, TEXT("Button Look"), WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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
    static HWND hwndButton[NUM];
    static RECT rect;
    static TCHAR szTop[]        = TEXT("message             wParam      lParam");
    static TCHAR szUndLine[]    = TEXT("-------             ------      ------");
    static TCHAR szFormat[]     = TEXT("%-16s%04X-%04X      %04X-%04X");
    static TCHAR szBuffer[50];
    static int cxChar, cyChar;
    HDC hdc;
    PAINTSTRUCT ps;
    int i;

    switch (message) {
        case WM_CREATE: {
                cxChar = LOWORD(GetDialogBaseUnits());
                cyChar = HIWORD(GetDialogBaseUnits());

                for (i=0; i<NUM; ++i) {
                    TCHAR className[] = TEXT("button");
                    DWORD style = WS_CHILD | WS_VISIBLE | button[i].iStyle;
                    int x = cxChar;
                    int y = cyChar * (1 + 2 * i);
                    int width = 20 * cxChar;
                    int height = 7 * cyChar / 4;
                    HMENU hmenu = (HMENU) i;
                    HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;

                    hwndButton[i] = CreateWindow(className,
                                                button[i].szText,
                                                style,
                                                x, y, width, height,
                                                hwnd, hmenu,
                                                hInst, NULL);
                }
            }
            return 0;
        case WM_SIZE:
            rect.left = 24 * cxChar;
            rect.top = 2 * cyChar;
            rect.right = LOWORD(lParam);
            rect.bottom = HIWORD(lParam);
            return 0;
        case WM_PAINT:
            InvalidateRect(hwnd, &rect, TRUE);
            hdc = BeginPaint(hwnd, &ps);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            SetBkMode(hdc, TRANSPARENT);
            TextOut(hdc, 24 * cxChar, cyChar, szTop, lstrlen(szTop));
            TextOut(hdc, 24 * cxChar, cyChar, szUndLine, lstrlen(szUndLine));
            EndPaint(hwnd, &ps);
            return 0;
        case WM_DRAWITEM:
        case WM_COMMAND:
            ScrollWindow(hwnd, 0, -cyChar, &rect, &rect);
            hdc = GetDC(hwnd);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            TextOut(hdc, 24 * cxChar, cyChar * (rect.bottom / cyChar - 1),
                szBuffer,
                wsprintf(szBuffer, szFormat,
                message == WM_DRAWITEM ? TEXT("WM_DRAWITEM") : TEXT("WM_COMMAND"),
                HIWORD(wParam), LOWORD(wParam),
                HIWORD(lParam), LOWORD(lParam)));
            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
