#include "slider.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QStringBuilder>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

#include "slider_p.h"

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new SliderPrivate(this))
{
    d_func()->init(this);
}

Slider::~Slider()
{
}

QSize Slider::minimumSizeHint() const
{
    return QSize(20, 20);
}

int Slider::thumbOffset() const
{
    return Style::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? rect().width() - SLIDER_MARGIN*2
            : rect().height() - SLIDER_MARGIN*2,
        invertedAppearance());
}

void Slider::setPageStepMode(bool pageStep)
{
    Q_D(Slider);

    d->pageStepMode = pageStep;
}

bool Slider::pageStepMode() const
{
    Q_D(const Slider);

    return d->pageStepMode;
}

void Slider::setTrackColor(const QColor &color)
{
    Q_D(Slider);

    d->trackColor = color;
    update();
}

QColor Slider::trackColor() const
{
    Q_D(const Slider);

    return d->trackColor;
}

void Slider::setTrackWidth(int width)
{
    Q_D(Slider);

    d->trackWidth = width;
    update();
}

int Slider::trackWidth() const
{
    Q_D(const Slider);

    return d->trackWidth;
}

void Slider::sliderChange(SliderChange change)
{
    Q_D(Slider);

    if (SliderOrientationChange == change) {
        QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (orientation() == Qt::Vertical)
            sp.transpose();
        setSizePolicy(sp);
    } else if (SliderValueChange == change) {
        if (minimum() == value()) {
            triggerAction(SliderToMinimum);
            emit changedToMinimum();
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        } else if (minimum() == d->oldValue) {
            emit changedFromMinimum();
        }
        d->oldValue = value();
    }
    QAbstractSlider::sliderChange(change);
}

void Slider::changeEvent(QEvent *event)
{
    if (QEvent::EnabledChange == event->type()) {
        if (isEnabled()) {
            emit sliderEnabled();
        } else {
            emit sliderDisabled();
        }
    }
    QAbstractSlider::changeEvent(event);
}

void Slider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Slider);

    QPainter painter(this);

    d->paintTrack(&painter);

#ifdef DEBUG_LAYOUT
    if (hasFocus())
        painter.drawRect(rect().adjusted(0, 0, -1, -1));

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

    if (isSliderDown())
    {
        setSliderPosition(d->valueFromPosition(event->pos()));
    }
    else
    {
        QRectF track(d->trackGeometry().adjusted(-2, -2, 2, 2));

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
        setSliderDown(true);
        return;
    }

    if (!d->pageStepMode) {
        setSliderPosition(d->valueFromPosition(event->pos()));
        d->thumb->setHaloSize(0);
        setSliderDown(true);
        return;
    }

    d->step = true;
    d->stepTo = d->valueFromPosition(pos);

    SliderAction action = d->stepTo > sliderPosition()
        ? SliderPageStepAdd
        : SliderPageStepSub;

    triggerAction(action);
    setRepeatAction(action);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(Slider);

    if (isSliderDown()) {
        setSliderDown(false);
    } else if (d->step) {
        d->step = false;
        setRepeatAction(SliderNoAction, 0);
    }

    QAbstractSlider::mouseReleaseEvent(event);
}
