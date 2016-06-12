#ifndef RADIOBUTTON_P_H
#define RADIOBUTTON_P_H

#include <QObject>
#include <QStateMachine>
#include "radiobutton_internal.h"

class RadioButton;
class RippleOverlay;

class RadioButtonPrivate
{
    Q_DISABLE_COPY(RadioButtonPrivate)
    Q_DECLARE_PUBLIC(RadioButton)

public:
    RadioButtonPrivate(RadioButton *q);

    void init();

    void assignAnimationProperties();
    void updatePalette();

    RadioButton     *const q_ptr;
    RippleOverlay   *ripple;
    RadioButtonIcon *checkedIcon;
    RadioButtonIcon *uncheckedIcon;
    QStateMachine   *machine;
    QState          *uncheckedState;
    QState          *checkedState;
    int              iconSize;
    QColor           checkedColor;
    QColor           uncheckedColor;
    QColor           textColor;
    QColor           disabledColor;
    bool             useThemeColors;
};

#endif // RADIOBUTTON_P_H
