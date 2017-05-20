#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <windows.h>

class Application {
public:
    WPARAM run() {
        MSG msg;

    	while (GetMessage(&msg, NULL, 0, 0)) {
    		TranslateMessage(&msg);
    		DispatchMessage(&msg);
    	}

    	return msg.wParam;
    }
};

#endif // APPLICATION_H_
