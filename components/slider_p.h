#ifndef SLIDER_P_H
#define SLIDER_P_H

#include <QPainter>
#include <QApplication>
#include "lib/style.h"
#include "slider.h"
#include "slidertrack.h"
#include "sliderthumb.h"
#include "sliderstatemachine.h"

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

public:
    SliderPrivate(Slider *parent);

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    Slider             *const q_ptr;
    SliderThumb        *const thumb;
    SliderTrack        *const track;
    SliderStateMachine *const machine;
    bool hoverTrack;
    bool hoverThumb;
    bool hover;
    bool step;
    bool pageStepMode;
    int  stepTo;
    int  oldValue;
    int  trackWidth;
};

SliderPrivate::SliderPrivate(Slider *q)
    : q_ptr(q),
      thumb(new SliderThumb(q)),
      track(new SliderTrack(q)),
      machine(new SliderStateMachine(q, thumb, track)),
      hoverTrack(false),
      hoverThumb(false),
      hover(false),
      step(false),
      pageStepMode(true),
      stepTo(0),
      oldValue(q->value()),
      trackWidth(2)
{
    q->setMouseTracking(true);
    q->setFocusPolicy(Qt::StrongFocus);
    q->setPageStep(1);

    QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
    if (q->orientation() == Qt::Vertical)
        sp.transpose();
    q->setSizePolicy(sp);
    q->setAttribute(Qt::WA_WState_OwnSizePolicy, false);

    machine->start();

    QCoreApplication::processEvents();
}

QRectF SliderPrivate::trackBoundingRect() const
{
    Q_Q(const Slider);

    qreal hw = static_cast<qreal>(trackWidth)/2;

    return Qt::Horizontal == q->orientation()
        ? QRectF(SLIDER_MARGIN, q->height()/2 - hw,
                 q->width() - SLIDER_MARGIN*2, hw*2)
        : QRectF(q->width()/2 - hw, SLIDER_MARGIN, hw*2,
                 q->height() - SLIDER_MARGIN*2);
}

QRectF SliderPrivate::thumbBoundingRect() const
{
    Q_Q(const Slider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(q->thumbOffset(), q->height()/2 - SLIDER_MARGIN,
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2)
        : QRectF(q->width()/2 - SLIDER_MARGIN, q->thumbOffset(),
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2);
}

int SliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const Slider);

    int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    int span = Qt::Horizontal == q->orientation()
        ? q->width() - SLIDER_MARGIN*2
        : q->height() - SLIDER_MARGIN*2;

    return Style::sliderValueFromPosition(
                q->minimum(),
                q->maximum(),
                position - SLIDER_MARGIN,
                span,
                q->invertedAppearance());
}

void SliderPrivate::setHovered(bool status)
{
    Q_Q(Slider);

    if (hover != status) {
        hover = status;
        if (!q->hasFocus())  {
            if (status) {
                emit machine->noFocusMouseEnter();
            } else {
                emit machine->noFocusMouseLeave();
            }
        }
        q->update();
    }
}

#endif // SLIDER_P_H
