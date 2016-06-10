#ifndef SLIDER_P_H
#define SLIDER_P_H

#include <QPainter>
#include <QApplication>
#include "lib/style.h"
#include "slider.h"
#include "slider_internal.h"

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

public:
    SliderPrivate(Slider *q)
        : q_ptr(q),
          hoverTrack(false),
          hoverThumb(false),
          hover(false),
          step(false),
          pageStepMode(true),
          stepTo(0),
          oldValue(0),
          trackWidth(2),
          useThemeColors(true)
    {}

    void init();

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    Slider *const q_ptr;
    SliderThumb *thumb;
    SliderTrack *track;
    SliderStateMachine *machine;
    bool hoverTrack;
    bool hoverThumb;
    bool hover;
    bool step;
    bool pageStepMode;
    int  stepTo;
    int  oldValue;
    int  trackWidth;
    QColor thumbColor;
    QColor trackColor;
    QColor disabledColor;
    bool useThemeColors;
};

#endif // SLIDER_P_H
