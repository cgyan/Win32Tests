#ifndef WIN32EVENTQUEUE_H_
#define WIN32EVENTQUEUE_H_

#include "EventQueue.h"
#include <windows.h>
class Event;
class Object;

class Win32EventQueue : public EventQueue {
private:
    MSG msg;
public:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
    Event * nextEvent() override;
};

#endif // WIN32EVENTQUEUE_H_
