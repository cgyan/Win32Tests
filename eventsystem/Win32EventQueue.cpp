#include "Win32EventQueue.h"
#include "Application.h"
#include "Object.h"
#include "CloseEvent.h"

Event *
Win32EventQueue::nextEvent() {
    GetMessage(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    return &Win32EventQueue::currentEvent;
}

LRESULT
Win32EventQueue::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // EventQueue::currentEvent;
    EventQueue::currentReceiver = nullptr;

    switch (message) {
        case WM_CLOSE: {
            EventQueue::currentEvent = CloseEvent(Event::Close);
            EventQueue::currentReceiver = (Object *)GetWindowLongPtr(hwnd, GWLP_USERDATA);;
            break;
        }
        case WM_DESTROY:
            Application::shouldKeepRunning = false;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
