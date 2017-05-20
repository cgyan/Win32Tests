#include "Win32RunLoop.h"
#include "Application.h"
#include "CloseEvent.h"
class Object;

void
Win32RunLoop::processNextEvent() {
    GetMessage(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

LRESULT
Win32RunLoop::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CLOSE: {
            Event event = CloseEvent(Event::Close);
            Object * receiver = (Object *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            Application::sendEvent(receiver, &event);
            break;
        }
        case WM_DESTROY:
            RunLoop::stop();
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
