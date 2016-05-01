#include "slider.h"
#include "slider_p.h"

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new SliderPrivate(this))
{
}

Slider::~Slider()
{
}
