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
    window.show();

    return app.run();
}
