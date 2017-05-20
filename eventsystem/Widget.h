#ifndef WIDGET_H_
#define WIDGET_H_

#include "Object.h"
#include <WinDef.h> //  for HWND

class WidgetImpl;
class CloseEvent;
class ResizeEvent;
class MouseEvent;

class Widget : public Object {
protected:
                    Widget(WidgetImpl * impl, Widget * parent);
public:
                    Widget(Widget * parent = nullptr);
	virtual         ~Widget();

    HWND           hwnd() const;
    void           setParent(Widget *parent);

    void           setTitle(const std::string& newTitle);
	void           show();
    void           resize(const int width, const int height);
    const int      width() const;
    const int      height() const;
protected:
    virtual void   handleEvent(Event * e) override;
    virtual void   onClose(CloseEvent * e);
    virtual void   onResize(ResizeEvent * e);
    virtual void   onMousePress(MouseEvent * e);
protected:
    WidgetImpl * impl;
};

#endif // WIDGET_H_
