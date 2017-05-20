#ifndef MESSAGEROUTER_H_
#define MESSAGEROUTER_H_

#include <windows.h>
#include "WindowImpl.h"

class MessageRouter {
public:
    static LRESULT CALLBACK
	MainMsgRouter(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		if (message == WM_NCCREATE) {
            SetWindowLongPtr(hwnd, GWLP_USERDATA, LONG_PTR((LPCREATESTRUCT(lParam))->lpCreateParams));
        }

        WindowImpl * windowImpl = (WindowImpl*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (windowImpl) {
            return windowImpl->handleMessage(hwnd, message, wParam, lParam);
        }
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
};

#endif // MESSAGEROUTER_H_
