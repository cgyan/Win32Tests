#ifndef WIDGETVIEW_H_
#define WIDGETVIEW_H_

class WidgetModel;
class Object;

class WidgetView {
protected:
    WidgetModel * m_model;
private:
    Object * m_observer;
private:
    WidgetView() = delete;
public:
    WidgetView(Object * observer) // called by ButtonView ctor
    :   m_model{nullptr},
        m_observer{observer}
    {}

    WidgetView(WidgetModel* model, Object * observer) // called by subclass ctor
    :   m_model{model},
        m_observer{observer}
    {}

    virtual ~WidgetView() {
        //
    }

    Object *
    observer() const {
        return this->m_observer;
    }

    virtual void create() = 0;
    virtual void update() = 0;
    virtual void show() = 0;
    virtual void resize(const int width, const int height) = 0;
    virtual HWND hwnd() const = 0;
public:
    virtual void attachToParentWidget(Widget * parent) { std::cout << "Should not be called \n"; }
};









#endif // WIDGETVIEW_H_
