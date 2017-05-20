#include <windows.h>
#include "Application.h"
#include "Window.h"
#include "Button.h"
#include <iostream>

/*
class Event {
public:
	enum class Type { MousePress, KeyPress, WindowResize };
	Type type;
}

class MouseEvent : public Event {
public:
	MouseEvent(Event::Type etype); // e.g. etype == MousePress
}

using ObserverToEventMap = std::map<Observer *, std::list<Event::type>>
ObserverToEventMap ob2evMap;

MessageRouter::registerObserverForEvent(Observer * observer, Event::Type etype) {
	ob2evMap[observer].push_back(etype);
}

MessageRouter::MainMessageRouter:
---------------------------------
-- If MainWindow event:					If Control event:
-- hwnd 	- main window handle		hwnd 			- main window handle
-- lParam 	- window specific			(HWND)lParam 	- control handle
-- wParam 	- window specific			LOWORD(wParam) 	- control identifier
-- 										HIWORD(wParam)	- notification code

LRESULT CALLBACK
MessageRouter::MainMessageRouter(HWND, UINT, WPARAM ,LPARAM) {

	// VERSION 2
	switch (message) {
		case WM_COMMAND:
			return handleCommandMessage(hwnd, message, wParam, lParam);
		case WM_SIZE:
			return handleSizeMessage(hwnd, message, wParam, lParam);
		case WM_DESTROY:
			return handleDestroyMessage();
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

const bool
MessageRouter::observerRegisteredForEvent(Observer *, Event::Type) {
	std::list<Event::Type> events = ob2evMap.find(observer)->second;
	if (events.contains(Event::Type::MousePress)) return true;
	return false;
}

LRESULT CALLBACK
MessageRouter::handleCommandMessage(HWND, UINT, WPARAM, LPARAM) {
	Observer * observer = (Observer *)GetWindowLongPtr((HWND)lParam, GWLP_USERDATA);
	notificationCode = HIWORD(wParam);

	switch (notificationCode) {
		case BN_CLICKED:
			if (observerRegisteredForEvent(observer, Event::Type::MousePress) {
				MouseEvent e(Event::Type::MousePress);
				observer->handleEvent(e);
			}
			break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK
MessageRouter::handleSizeMessage(HWND, UINT, WPARAM, LPARAM) {
	Observer * observer = (Observer *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	if (observerRegisteredForEvent(observer, Event::Type::WindowResize)) {
		WindowEvent e(Event::Type::WindowResize);
		observer->handleEvent(e);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT
MessageRouter::handleDestroyMessage() {
	PostQuitMessage(0);
	return 0;
}
//=============================================================================================


// VERSION 1a
switch (message) {
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
			case BN_CLICKED:
				Observer * observer = getObserverFromLParam((HWND)lParam);
				std::list<Observer *> observers = ev2obMap.find(Event::Type::MousePress)->second;
				if (observers.contains(observer))
					observer->handleEvent(MouseEvent(Event::Type::MousePress));
				return 0;
		}
		return 0;
}

// VERSION 1b
switch (message) {
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
			case BN_CLICKED:
				std::list<HWND> hwnds = ev2hwndMap.find(Event::Type::MousePress)->second;
				Observer * observer = getObserverFromHwnd(hwnd);
				if (observers.contain(observer))
					observer->handleEvent(MouseEvent(Event::Type::MousePress));
				return 0;
		}
		return 0;
}

// VERSION 3
switch (message) {
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
			case BN_CLICKED:
				std::map<HWND, Observer *> hwnd2obMap = ev2obMap.find(Event::Type::MousePress)->second;
				if ((it = hwnd2obMap.find(hwnd)) != hwnd2obMap.end())
					it->handleEvent(MouseEvent(Event::Type::MousePress));
				return 0;
		}
		return 0;
}
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

	Application app;
	Window w;
	w.show();

	Button btn(&w);
	// button.addHandler(prism::MouseEvent::CLICK, onClick);
	btn.show();

	return app.run();
}
