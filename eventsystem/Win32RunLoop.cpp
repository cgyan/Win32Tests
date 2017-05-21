#include "Win32RunLoop.h"
#include "Application.h"
#include "CloseEvent.h"
#include "MouseEvent.h"
#include "ResizeEvent.h"
#include <iostream>
#include <cassert>
#include <memory>
class Object;
class Button;

void
Win32RunLoop::processNextEvent() {
    GetMessage(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

LRESULT
Win32RunLoop::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_SIZE: {
            Object * receiver = (Object *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            std::shared_ptr<Event> event = std::make_shared<ResizeEvent>(Event::Resize, LOWORD(lParam), HIWORD(lParam));
            Application::sendEvent(receiver, event.get());
            break;
        }
        case WM_COMMAND: {
            HWND winHndl = (HWND)lParam;
            Object * receiver = (Object *)GetWindowLongPtr(winHndl, GWLP_USERDATA);
            std::shared_ptr<Event> event = std::make_shared<MouseEvent>(Event::MousePress);
            Application::sendEvent(receiver, event.get());
            break;
        }
        case WM_CLOSE: {
            Object * receiver = (Object *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
            std::shared_ptr<Event> event = std::make_shared<CloseEvent>(Event::Close);
            Application::sendEvent(receiver, event.get());
            break;
        }
        case WM_DESTROY:
            RunLoop::stop();
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
