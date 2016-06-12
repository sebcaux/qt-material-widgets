#ifndef RAISEDBUTTON_P_H
#define RAISEDBUTTON_P_H

#include "flatbutton_p.h"

class QGraphicsDropShadowEffect;

class RaisedButtonPrivate : public FlatButtonPrivate
{
    Q_DISABLE_COPY(RaisedButtonPrivate)
    Q_DECLARE_PUBLIC(RaisedButton)

public:
    RaisedButtonPrivate(RaisedButton *q);
    ~RaisedButtonPrivate();

    void init();

    QStateMachine machine;
    QState *normalState;
    QState *pressedState;
    QGraphicsDropShadowEffect *effect;
    QColor disabledBackgroundColor;
};

#endif // RAISEDBUTTON_P_H
