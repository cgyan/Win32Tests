#ifndef BUTTON_H_
#define BUTTON_H_

#include "Widget.h"
#include <string>

class Button : public Widget {
public:
                    Button(Widget * parent = nullptr);
    virtual         ~Button();

    void            setText(const std::string& text);

    virtual void    onResize(ResizeEvent * e) override;
    virtual void    onMousePress(MouseEvent * e) override;
};





#endif // BUTTON_H_
