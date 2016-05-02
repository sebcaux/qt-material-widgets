#include "slider.h"
#include <QPainter>
#include <QStringBuilder>
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

    painter.setFont(QFont("monospace", 8));
    painter.drawText(8, 18, "Value: " % QString::number(value()));
    painter.drawText(8, 36, "Position: " % QString::number(sliderPosition()));
#endif
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(Slider);

    QRect track(d->trackGeometry().adjusted(-2, -2, 2, 2));

    if (track.contains(event->pos()) != d->hoverTrack) {
        d->hoverTrack = !d->hoverTrack;
        update();
    }

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbGeometry().center());

    if (thumb.contains(event->pos()) != d->hoverThumb) {
        d->hoverThumb = !d->hoverThumb;
        update();
    }

    QAbstractSlider::mouseMoveEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(Slider);

    QRect track(d->trackGeometry().adjusted(-2, -2, 2, 2));

    if (track.contains(event->pos())) {
        setValue(d->valueFromPosition(event->pos()));
    }

    QAbstractSlider::mouseReleaseEvent(event);
}
