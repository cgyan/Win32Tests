#include "Application.h"
#include "Widget.h"
#include "DerivedWidget.h"
#include "Button.h"
#include <cassert>
#include <iostream>
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    Application app;

    DerivedWidget window;
    window.setTitle("The window title");
    window.resize(600, 600);
    window.show();
    cout << "window width is " << window.width() << " and window height is " << window.height() << std::endl;

    Button btn;
    btn.resize(600, 100);
    btn.setParent(&window);
    btn.setTitle("Click");

    return app.run();
}
