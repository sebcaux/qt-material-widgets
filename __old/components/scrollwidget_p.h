#ifndef SCROLLWIDGET_P_H
#define SCROLLWIDGET_P_H

#include <QObject>
#include <QColor>

class ScrollBar;
class ScrollBarStateMachine;

class ScrollBarPrivate
{
    Q_DISABLE_COPY(ScrollBarPrivate)
    Q_DECLARE_PUBLIC(ScrollBar)

public:
    ScrollBarPrivate(ScrollBar *q);
    ~ScrollBarPrivate();

    void init();

    ScrollBar             *const q_ptr;
    ScrollBarStateMachine *const machine;
    QColor                       backgroundColor;
    QColor                       sliderColor;
    QColor                       canvasColor;
    bool                         hideOnMouseOut;
    bool                         useThemeColors;
};

#endif // SCROLLWIDGET_P_H
