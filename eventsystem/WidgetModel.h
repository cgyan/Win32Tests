#ifndef WIDGETMODEL_H_
#define WIDGETMODEL_H_

#include <string>

class WidgetModel {
private:
    std::string m_title;
    int m_width;
    int m_height;
public:
    WidgetModel()
    :   m_title{},
        m_width{0},
        m_height{0}
    {}

    void
    setTitle(const std::string& newTitle) {
        m_title = newTitle;
    }

    const std::string
    title() const {
        return m_title;
    }

    void
    setSize(const int newWidth, const int newHeight) {
        this->m_width = newWidth;
        this->m_height = newHeight;
    }

    const int
    width() const {
        return this->m_width;
    }

    const int
    height() const {
        return this->m_height;
    }
};





#endif // WIDGETMODEL_H_
