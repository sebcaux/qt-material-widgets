#ifndef SLIDER_P_H
#define SLIDER_P_H

#include "slider.h"

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

public:
    SliderPrivate(Slider *parent)
        : q_ptr(parent)
    {
    }

    Slider *const q_ptr;
};

#endif // SLIDER_P_H
