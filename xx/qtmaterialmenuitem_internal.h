#ifndef QTMATERIALMENUITEM_INTERNAL_H
#define QTMATERIALMENUITEM_INTERNAL_H

#include <QStateMachine>
#include <QColor>
#include "xx/qtmaterialmenuitem.h"

class QtMaterialMenuItem;

class QtMaterialMenuItemStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)

public:
    explicit QtMaterialMenuItemStateMachine(QtMaterialMenuItem *menuItem);
    ~QtMaterialMenuItemStateMachine();

    inline void setForegroundColor(const QColor &color);
    inline QColor foregroundColor() const;

signals:
    void highlight();
    void unhighlight();

private:
    Q_DISABLE_COPY(QtMaterialMenuItemStateMachine)

    QtMaterialMenuItem *const m_menuItem;
    QState             *const m_defaultState;
    QState             *const m_highlightedState;
    QColor                    m_foregroundColor;
};

inline void QtMaterialMenuItemStateMachine::setForegroundColor(const QColor &color)
{
    m_foregroundColor = color;
    m_menuItem->update();
}

inline QColor QtMaterialMenuItemStateMachine::foregroundColor() const
{
    return m_foregroundColor;
}

#endif // QTMATERIALMENUITEM_INTERNAL_H
