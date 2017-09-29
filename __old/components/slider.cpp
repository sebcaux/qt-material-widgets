#include "slider.h"
#include "slider_p.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QStringBuilder>
#include <QMouseEvent>
#include <QApplication>

SliderPrivate::SliderPrivate(Slider *q)
    : q_ptr(q),
      thumb(new SliderThumb(q)),
      track(new SliderTrack(q)),
      machine(0),
      hoverTrack(false),
      hoverThumb(false),
      hover(false),
      step(false),
      pageStepMode(true),
      stepTo(0),
      oldValue(0),
      trackWidth(2),
      useThemeColors(true)
{
}

void SliderPrivate::init()
{
    Q_Q(Slider);

    machine = new SliderStateMachine(q, thumb, track);

    oldValue = q->value();

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

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
      d_ptr(new SliderPrivate(this))
{
    d_func()->init();
}

Slider::~Slider()
{
}

void Slider::setUseThemeColors(bool value)
{
    Q_D(Slider);

    d->useThemeColors = value;
    d->machine->updatePalette();
}

bool Slider::useThemeColors() const
{
    Q_D(const Slider);

    return d->useThemeColors;
}

void Slider::setThumbColor(const QColor &color)
{
    Q_D(Slider);

    d->thumbColor = color;
    setUseThemeColors(false);
}

QColor Slider::thumbColor() const
{
    Q_D(const Slider);

    if (d->useThemeColors || !d->thumbColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->thumbColor;
    }
}

void Slider::setTrackColor(const QColor &color)
{
    Q_D(Slider);

    d->trackColor = color;
    setUseThemeColors(false);
}

QColor Slider::trackColor() const
{
    Q_D(const Slider);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return Style::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

void Slider::setDisabledColor(const QColor &color)
{
    Q_D(Slider);

    d->disabledColor = color;
    setUseThemeColors(false);
}

QColor Slider::disabledColor() const
{
    Q_D(const Slider);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        return Style::instance().themeColor("disabled");
    } else {
        return d->disabledColor;
    }
}

QSize Slider::minimumSizeHint() const
{
    return Qt::Horizontal == orientation()
            ? QSize(20, 34)
            : QSize(34, 20);
}

int Slider::thumbOffset() const
{
    return Style::sliderPositionFromValue(
        minimum(),
        maximum(),
        sliderPosition(),
        Qt::Horizontal == orientation()
            ? width() - SLIDER_MARGIN*2
            : height() - SLIDER_MARGIN*2,
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

bool Slider::hovered() const
{
    Q_D(const Slider);

    return d->hover;
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
            emit d->machine->changedToMinimum();
        } else if (maximum() == value()) {
            triggerAction(SliderToMaximum);
        }
        if (minimum() == d->oldValue) {
            emit d->machine->changedFromMinimum();
        }
        d->oldValue = value();
    }
    QAbstractSlider::sliderChange(change);
}

void Slider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

#ifdef DEBUG_LAYOUT
    QPainter painter(this);

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
        QRectF track(d->trackBoundingRect().adjusted(-2, -2, 2, 2));

        if (track.contains(event->pos()) != d->hoverTrack) {
            d->hoverTrack = !d->hoverTrack;
            update();
        }

        QRectF thumb(0, 0, 16, 16);
        thumb.moveCenter(d->thumbBoundingRect().center());

        if (thumb.contains(event->pos()) != d->hoverThumb) {
            d->hoverThumb = !d->hoverThumb;
            update();
        }

        d->setHovered(d->hoverTrack || d->hoverThumb);
    }

    QAbstractSlider::mouseMoveEvent(event);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    Q_D(Slider);

    const QPoint pos = event->pos();

    QRectF thumb(0, 0, 16, 16);
    thumb.moveCenter(d->thumbBoundingRect().center());

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
    setRepeatAction(action, 400, 8);
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

void Slider::leaveEvent(QEvent *event)
{
    Q_D(Slider);

    if (d->hoverTrack) {
        d->hoverTrack = false;
        update();
    }
    if (d->hoverThumb) {
        d->hoverThumb = false;
        update();
    }

    d->setHovered(false);

    QAbstractSlider::leaveEvent(event);
}
