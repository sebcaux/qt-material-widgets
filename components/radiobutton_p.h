#ifndef RADIOBUTTON_P_H
#define RADIOBUTTON_P_H

#include <QObject>

class RadioButton;
class RippleOverlay;

class RadioButtonPrivate
{
    Q_DISABLE_COPY(RadioButtonPrivate)
    Q_DECLARE_PUBLIC(RadioButton)

public:
    RadioButtonPrivate(RadioButton *q);

    void init();

    RadioButton   *const q_ptr;
    RippleOverlay *ripple;
};

#endif // RADIOBUTTON_P_H
