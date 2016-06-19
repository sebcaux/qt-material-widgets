#ifndef SCROLLBAR_P_H
#define SCROLLBAR_P_H

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

#endif // SCROLLBAR_P_H
