#ifndef TOGGLE_P_H
#define TOGGLE_P_H

#include "toggle_internal.h"

class TogglePrivate
{
    Q_DISABLE_COPY(TogglePrivate)
    Q_DECLARE_PUBLIC(Toggle)

public:
    TogglePrivate(Toggle *q);

    void init();

    Toggle *const q_ptr;
};

#endif // TOGGLE_P_H
