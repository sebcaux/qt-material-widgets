#ifndef SLIDER_P_H
#define SLIDER_P_H

#include "slider.h"
#include <QPainter>

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
    Q_DECLARE_PUBLIC(Slider)

public:
    SliderPrivate(Slider *parent)
        : q_ptr(parent),
          orientation(Qt::Horizontal)
    {
    }

    QRect trackGeometry() const
    {
        Q_Q(const Slider);

        return Qt::Horizontal == orientation
            ? QRect(0, q->rect().height()/2 - 1, q->rect().width(), 2)
            : QRect(q->rect().width()/2 - 1, 0, 2, q->rect().height());
    }

    void paintTrack(QPainter *painter)
    {
        Q_Q(Slider);

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(0, 0, 0, 255));

        painter->save();
        painter->fillRect(trackGeometry(), brush);
        painter->restore();

#ifdef DEBUG_LAYOUT
        painter->drawRect(q->rect().adjusted(1, 1, -2, -2));
#endif
    }

    void paintThumb(QPainter *painter)
    {
        painter->save();

        painter->restore();
    }

    Slider *const q_ptr;

    Qt::Orientation orientation;
};

#endif // SLIDER_P_H
