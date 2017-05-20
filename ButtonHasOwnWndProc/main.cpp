#include <windows.h>
#include <CommCtrl.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MyButtonWndProc(HWND, UINT, WPARAM, LPARAM);

HWND hMainWindow;
HWND hButton;
HWND hButton2;
WNDPROC oldProc;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR szCmdLine, int iCmdShow) {
    static TCHAR szAppName[] = TEXT("ButtonHasOwnWndProc");
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

    hMainWindow = CreateWindowEx(
        0,
        szAppName,
        TEXT("Button has own WndProc function"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hMainWindow, iCmdShow);
    UpdateWindow(hMainWindow);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
        case WM_CREATE: {
            int x = 10;
            int y = 10;
            int width = 100;
            int height = 20;

            hButton = CreateWindowEx(
                0,
                WC_BUTTON,
                "Click me!",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                x,y,width,height,
                hwnd,
                (HMENU)111,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            hButton2 = CreateWindowEx(
                0,
                WC_BUTTON,
                "Press me!",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                x,100,width,height,
                hwnd,
                (HMENU)112,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );
            // oldProc = (WNDPROC)SetWindowLongPtr(hButton, GWLP_WNDPROC, intptr_t(MyButtonWndProc));
            return 0;
        }
        case WM_COMMAND: {
            HWND wndBtn = (HWND)lParam;
            uint32_t controlId = LOWORD(wParam);
            uint32_t notificationCode = HIWORD(wParam);

            if (wndBtn == hButton && controlId == 111 && notificationCode == BN_CLICKED)
                std::cout << "click me clicked" << std::endl;
            if (wndBtn == hButton2 && controlId == 112 && notificationCode == BN_CLICKED)
                std::cout << "press me clicked" << std::endl;

            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);

}
