#include "slider.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include "slider_p.h"

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new SliderPrivate(this))
{
}

Slider::~Slider()
{
}

void Slider::setOrientation(Qt::Orientation orientation)
{
    Q_D(Slider);
    d->orientation = orientation;
    update();
}

Qt::Orientation Slider::orientation() const
{
    Q_D(const Slider);
    return d->orientation;
}

void Slider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Slider);

    QPainter painter(this);

    d->paintTrack(&painter);
    d->paintThumb(&painter);

#ifdef DEBUG_LAYOUT
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setOpacity(1);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(Slider);

    QRect track(d->trackGeometry().adjusted(-2, -2, 2, 2));
    const bool onTrack = track.contains(event->pos());

    if (onTrack != d->hoverTrack) {
        d->hoverTrack = onTrack;
        update();
    }

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbGeometry().center());
    const bool onThumb = thumb.contains(event->pos());

    if (onThumb != d->hoverThumb) {
        d->hoverThumb = onThumb;
        update();
    }

    QAbstractSlider::mouseMoveEvent(event);
}
