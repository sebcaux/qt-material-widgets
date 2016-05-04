#ifndef SLIDER_P_H
#define SLIDER_P_H

#include "slider.h"
#include <QPainter>
#include "lib/style.h"

#define THUMB_OUTER_SIZE 30

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

public:
    SliderPrivate(Slider *parent)
        : q_ptr(parent),
          hoverTrack(false),
          hoverThumb(false),
          step(false),
          stepTo(0)
    {
        parent->setMouseTracking(true);
    }

    QRect trackGeometry() const
    {
        Q_Q(const Slider);

        return Qt::Horizontal == q->orientation()
            ? QRect(THUMB_OUTER_SIZE/2, q->rect().height()/2 - 1,
                    q->rect().width() - THUMB_OUTER_SIZE, 2)
            : QRect(q->rect().width()/2 - 1, THUMB_OUTER_SIZE/2, 2,
                    q->rect().height() - THUMB_OUTER_SIZE);
    }

    void paintTrack(QPainter *painter)
    {
        painter->save();

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(0, 0, 0, 255));

        painter->fillRect(trackGeometry(), brush);

        painter->restore();

#ifdef DEBUG_LAYOUT
        if (hoverTrack) {
            painter->save();
            painter->setPen(Qt::red);
            painter->drawRect(trackGeometry());
            painter->restore();
        }
#endif
    }

    QRectF thumbGeometry() const
    {
        Q_Q(const Slider);

        const int span = Qt::Horizontal == q->orientation()
            ? q->rect().width() - THUMB_OUTER_SIZE
            : q->rect().height() - THUMB_OUTER_SIZE;

        const int pos = Style::sliderPositionFromValue(
                    q->minimum(),
                    q->maximum(),
                    q->sliderPosition(),
                    span,
                    false);

        return Qt::Horizontal == q->orientation()
            ? QRectF(pos, q->rect().height()/2 - THUMB_OUTER_SIZE/2,
                     THUMB_OUTER_SIZE, THUMB_OUTER_SIZE)
            : QRectF(q->rect().width()/2 - THUMB_OUTER_SIZE/2, pos,
                     THUMB_OUTER_SIZE, THUMB_OUTER_SIZE);
    }

    void paintThumb(QPainter *painter)
    {
        painter->save();

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(0, 0, 0, 255));
        painter->setBrush(brush);

        painter->setRenderHint(QPainter::Antialiasing);

        QRectF thumb(0, 0, 12, 12);
        thumb.moveCenter(thumbGeometry().center());

        painter->drawEllipse(thumb);

        painter->restore();

#ifdef DEBUG_LAYOUT
        painter->drawRect(thumbGeometry());

        if (hoverThumb) {
            painter->save();
            painter->setPen(Qt::red);
            painter->drawRect(thumbGeometry());
            painter->restore();
        }
#endif
    }

    int valueFromPosition(const QPoint &pos) const
    {
        Q_Q(const Slider);

        int position = Qt::Horizontal == q->orientation() ? pos.x() : pos.y();

        int span = Qt::Horizontal == q->orientation()
            ? q->rect().width() - THUMB_OUTER_SIZE
            : q->rect().height() - THUMB_OUTER_SIZE;

        return Style::sliderValueFromPosition(
                    q->minimum(),
                    q->maximum(),
                    position - THUMB_OUTER_SIZE/2,
                    span,
                    false);
    }

    Slider *const q_ptr;

    bool hoverTrack;
    bool hoverThumb;
    bool step;
    int  stepTo;
};

#endif // SLIDER_P_H
