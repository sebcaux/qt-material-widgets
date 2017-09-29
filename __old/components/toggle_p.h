#ifndef TOGGLE_P_H
#define TOGGLE_P_H

#include <QStateMachine>
#include <QColor>

class RippleOverlay;
class Toggle;
class ToggleThumb;
class ToggleTrack;

class TogglePrivate
{
    Q_DISABLE_COPY(TogglePrivate)
    Q_DECLARE_PUBLIC(Toggle)

public:
    TogglePrivate(Toggle *q);

    void init();

    void updatePalette();

    Toggle         *const q_ptr;
    ToggleTrack    *const track;
    ToggleThumb    *const thumb;
    QState         *const offState;
    QState         *const onState;
    RippleOverlay  *const ripple;
    QStateMachine  *const machine;
    Qt::Orientation       orientation;
    QColor                disabledColor;
    QColor                activeColor;
    QColor                inactiveColor;
    QColor                trackColor;
    bool                  useThemeColors;
};

#endif // TOGGLE_P_H
