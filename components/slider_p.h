#ifndef SLIDER_P_H
#define SLIDER_P_H

#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "lib/style.h"
#include "slider.h"
#include "sliderthumb.h"
#include "sliderstatemachine.h"

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

    friend class SliderThumb;

public:
    SliderPrivate(Slider *parent);

    QRectF trackBoundingRect() const;
    QRectF thumbBoundingRect() const;

    void paintTrack(QPainter *painter);
    int valueFromPosition(const QPoint &pos) const;

    void setHovered(bool status);

    Slider             *const q_ptr;
    SliderThumb        *const thumb;
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

SliderPrivate::SliderPrivate(Slider *parent)
    : q_ptr(parent),
      thumb(new SliderThumb(parent)),
      machine(new SliderStateMachine(parent, thumb)),
      hoverTrack(false),
      hoverThumb(false),
      hover(false),
      step(false),
      pageStepMode(false),
      stepTo(0),
      oldValue(parent->value()),
      trackWidth(2)
{
    Q_Q(Slider);

    q->setMouseTracking(true);
    q->setFocusPolicy(Qt::StrongFocus);

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
        ? QRectF(SLIDER_MARGIN, q->rect().height()/2 - hw,
                q->rect().width() - SLIDER_MARGIN*2, hw*2)
        : QRectF(q->rect().width()/2 - hw, SLIDER_MARGIN, hw*2,
                q->rect().height() - SLIDER_MARGIN*2);
}

QRectF SliderPrivate::thumbBoundingRect() const
{
    Q_Q(const Slider);

    return Qt::Horizontal == q->orientation()
        ? QRectF(q->thumbOffset(), q->rect().height()/2 - SLIDER_MARGIN,
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2)
        : QRectF(q->rect().width()/2 - SLIDER_MARGIN, q->thumbOffset(),
                 SLIDER_MARGIN*2, SLIDER_MARGIN*2);
}

void SliderPrivate::paintTrack(QPainter *painter)
{
    Q_Q(const Slider);

    Style &style = Style::instance();

    painter->save();

    QBrush fg;
    fg.setStyle(Qt::SolidPattern);
    fg.setColor(q->isEnabled() ? style.themeColor("primary1")
                               : style.themeColor("disabled"));
    QBrush bg;
    bg.setStyle(Qt::SolidPattern);
    bg.setColor(hover ? QColor(0, 0, 0, 150)          // @TODO: set theme color
                      : style.themeColor("accent3"));

    qreal offset = q->thumbOffset() + SLIDER_MARGIN;

    QSizeF box(q->isEnabled() ? offset : offset - 7,
               qMax(q->width(), q->height()));

    if (Qt::Vertical == q->orientation())
        box.transpose();

    QRectF rect = Qt::Vertical == q->orientation()
        ? QRectF(0, q->isEnabled() ? offset : offset + 7,
                 box.width(), box.width())
        : QRectF(q->isEnabled() ? offset : offset + 7, 0,
                 box.height(), box.height());

    bool inverted = q->invertedAppearance();

    painter->fillRect(QRectF(QPointF(0, 0), box).intersected(trackBoundingRect()),
                      inverted ? bg : fg);
    painter->fillRect(rect.intersected(trackBoundingRect()), inverted ? fg : bg);

    painter->restore();

#ifdef DEBUG_LAYOUT
    if (hoverTrack) {
        painter->save();
        painter->setPen(Qt::red);
        painter->drawRect(trackBoundingRect());
        painter->restore();
    }
#endif
}

int SliderPrivate::valueFromPosition(const QPoint &pos) const
{
    Q_Q(const Slider);

    int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

    int span = Qt::Horizontal == q->orientation()
        ? q->rect().width() - SLIDER_MARGIN*2
        : q->rect().height() - SLIDER_MARGIN*2;

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
