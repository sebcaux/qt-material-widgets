#ifndef RADIOBUTTON_P_H
#define RADIOBUTTON_P_H

#include "lib/checkable_p.h"

class RadioButton;

class RadioButtonPrivate : public CheckablePrivate
{
    Q_DISABLE_COPY(RadioButtonPrivate)
    Q_DECLARE_PUBLIC(RadioButton)

public:
    RadioButtonPrivate(RadioButton *q);
    ~RadioButtonPrivate();

    void init();
};

#endif // RADIOBUTTON_P_H
