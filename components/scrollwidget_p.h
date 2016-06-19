#ifndef SCROLLWIDGET_P_H
#define SCROLLWIDGET_P_H

#include <QObject>

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

    ScrollBar *const q_ptr;
    ScrollBarStateMachine *machine;
    QColor          backgroundColor;
    QColor          sliderColor;
    bool            hideOnMouseOut;
    bool            useThemeColors;
};

#endif // SCROLLWIDGET_P_H
