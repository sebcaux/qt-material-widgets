#ifndef CHECKBOX_P_H
#define CHECKBOX_P_H

#include <QObject>
#include <QStateMachine>
#include "checkbox_internal.h"

class Checkbox;
class RippleOverlay;

class CheckboxPrivate
{
    Q_DISABLE_COPY(CheckboxPrivate)
    Q_DECLARE_PUBLIC(Checkbox)

public:
    CheckboxPrivate(Checkbox *q);

    void init();
    void updatePalette();

    Checkbox      *const q_ptr;
    RippleOverlay *ripple;
    CheckboxIcon  *checkedIcon;
    CheckboxIcon  *uncheckedIcon;
    QStateMachine *machine;
    QState        *uncheckedState;
    QState        *transitionState;
    QState        *checkedState;
    int            iconSize;
    QColor         checkedColor;
    QColor         uncheckedColor;
    QColor         textColor;
    QColor         disabledColor;
    bool           useThemeColors;
};

#endif // CHECKBOX_P_H
