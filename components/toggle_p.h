#ifndef TOGGLE_P_H
#define TOGGLE_P_H

#include <QStateMachine>

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

    Toggle *const q_ptr;
    ToggleTrack *const track;
    ToggleThumb *const thumb;
    RippleOverlay *const ripple;
    QStateMachine machine;
    Qt::Orientation orientation;
};

#endif // TOGGLE_P_H
