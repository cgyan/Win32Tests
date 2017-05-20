#ifndef WIN32RUNLOOP_H_
#define WIN32RUNLOOP_H_

#include "RunLoop.h"
#include <windows.h>

class Win32RunLoop : public RunLoop {
private:
    MSG msg;
public:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    void processNextEvent() override;
};

#endif // WIN32RUNLOOP_H_
