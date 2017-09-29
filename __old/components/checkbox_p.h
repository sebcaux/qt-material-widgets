#ifndef CHECKBOX_P_H
#define CHECKBOX_P_H

#include "lib/checkable_p.h"

class CheckBox;

class CheckBoxPrivate : public CheckablePrivate
{
    Q_DISABLE_COPY(CheckBoxPrivate)
    Q_DECLARE_PUBLIC(CheckBox)

public:
    CheckBoxPrivate(CheckBox *q);
    ~CheckBoxPrivate();

    void init();
};

#endif // CHECKBOX_P_H
