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
    connect(this, SIGNAL(actionTriggered(int)), this, SLOT(handleAction(int)));
}

Slider::~Slider()
{
}

void Slider::handleAction(int action)
{
    Q_D(Slider);

    if (!d->step)
        return;

    if ((SliderPageStepAdd == action && sliderPosition() > d->stepTo) ||
        (SliderPageStepSub == action && sliderPosition() < d->stepTo))
    {
        d->step = false;
        setRepeatAction(SliderNoAction);
        setSliderPosition(d->stepTo);
    }
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

    if (d->slide)
    {
        setSliderPosition(d->valueFromPosition(event->pos()));
    }
    else
    {
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
    }

    QAbstractSlider::mouseMoveEvent(event);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    Q_D(Slider);

    const QPoint pos = event->pos();

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbGeometry().center());

    if (thumb.contains(pos)) {
        d->slide = true;
        return;
    }

    QRect track(d->trackGeometry().adjusted(-2, -2, 2, 2));

    if (track.contains(pos)) {
        d->step = true;
        d->stepTo = d->valueFromPosition(pos);

        SliderAction action = d->stepTo > sliderPosition()
                ? SliderPageStepAdd
                : SliderPageStepSub;

        triggerAction(action);
        setRepeatAction(action, 200);
    }
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(Slider);

    if (d->slide) {
        d->slide = false;
        setValue(sliderPosition());
        return QAbstractSlider::mouseReleaseEvent(event);
    } else if (d->step) {
        d->step = false;
        setRepeatAction(SliderNoAction);
    }

    QAbstractSlider::mouseReleaseEvent(event);
}
