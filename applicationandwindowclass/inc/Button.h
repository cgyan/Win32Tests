#ifndef PRISM_BUTTON_H_
#define PRISM_BUTTON_H_

#include "Widget.h"

class Window;
class ButtonImpl;

class Button : public Widget {
private:
    ButtonImpl * impl;
public:
    Button(Window* parentWindow);
    ~Button();
    void show();
};

#endif //PRISM_BUTTON_H_
