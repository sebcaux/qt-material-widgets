#include "toggle.h"
#include "toggle_p.h"
#include <QPainter>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QApplication>
#include <QDebug>
#include "lib/rippleoverlay.h"
#include "lib/ripple.h"
#include "lib/style.h"
#include "toggle_internal.h"

TogglePrivate::TogglePrivate(Toggle *q)
    : q_ptr(q),
      track(new ToggleTrack(q)),
      thumb(new ToggleThumb(q)),
      offState(new QState),
      onState(new QState),
      ripple(new RippleOverlay(q->parentWidget())),
      machine(new QStateMachine),
      orientation(Qt::Horizontal),
      useThemeColors(true)
{
}

void TogglePrivate::init()
{
    Q_Q(Toggle);

    machine->setParent(q);

    q->setCheckable(true);
    q->setChecked(false);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    machine->addState(offState);
    machine->addState(onState);

    machine->setInitialState(offState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    //

    updatePalette();

    QObject::connect(q, SIGNAL(toggled(bool)), q, SLOT(addRipple()));

    machine->start();

    QCoreApplication::processEvents();
}

void TogglePrivate::updatePalette()
{
    Q_Q(Toggle);

    offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
    onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

    offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
    onState->assignProperty(thumb, "thumbColor", q->activeColor());

    q->update();
}

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new TogglePrivate(this))
{
    d_func()->init();
}

Toggle::~Toggle()
{
}

void Toggle::setUseThemeColors(bool value)
{
    Q_D(Toggle);

    d->useThemeColors = value;
    d->updatePalette();
}

bool Toggle::useThemeColors() const
{
    Q_D(const Toggle);

    return d->useThemeColors;
}

void Toggle::setDisabledColor(const QColor &color)
{
    Q_D(Toggle);

    d->disabledColor = color;
    setUseThemeColors(false);
}

QColor Toggle::disabledColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->disabledColor.isValid()) {
        QColor color = Style::instance().themeColor("disabled");
        color.setAlpha(30);
        return color;
    } else {
        return d->disabledColor;
    }
}

void Toggle::setActiveColor(const QColor &color)
{
    Q_D(Toggle);

    d->activeColor = color;
    setUseThemeColors(false);
}

QColor Toggle::activeColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->activeColor.isValid()) {
        return Style::instance().themeColor("primary1");
    } else {
        return d->activeColor;
    }
}

void Toggle::setInactiveColor(const QColor &color)
{
    Q_D(Toggle);

    d->inactiveColor = color;
    setUseThemeColors(false);
}

QColor Toggle::inactiveColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->inactiveColor.isValid()) {
        return Style::instance().themeColor("canvas");
    } else {
        return d->inactiveColor;
    }
}

void Toggle::setTrackColor(const QColor &color)
{
    Q_D(Toggle);

    d->trackColor = color;
    setUseThemeColors(false);
}

QColor Toggle::trackColor() const
{
    Q_D(const Toggle);

    if (d->useThemeColors || !d->trackColor.isValid()) {
        return Style::instance().themeColor("accent3");
    } else {
        return d->trackColor;
    }
}

QSize Toggle::sizeHint() const
{
    Q_D(const Toggle);

    return Qt::Horizontal == d->orientation
        ? QSize(64, 48)
        : QSize(48, 64);
}

Qt::Orientation Toggle::orientation() const
{
    Q_D(const Toggle);

    return d->orientation;
}

void Toggle::setOrientation(Qt::Orientation orientation)
{
    Q_D(Toggle);

    if (d->orientation == orientation)
        return;
    d->orientation = orientation;
}

void Toggle::updateOverlayGeometry()
{
    Q_D(Toggle);

    const qreal offset = d->thumb->offset();
    if (Qt::Horizontal == d->orientation) {
        d->ripple->setGeometry(geometry().adjusted(-10+offset, -20, 10+offset, 20));
    } else {
        d->ripple->setGeometry(geometry().adjusted(-10, -20+offset, 10, 20+offset));
    }
}

void Toggle::addRipple()
{
    Q_D(Toggle);

    int t, w;

    if (Qt::Horizontal == d->orientation) {
        t = height()/2;
        w = d->thumb->height()/2+10;
    } else {
        t = width()/2;
        w = d->thumb->width()/2+10;
    }

    Ripple *ripple = new Ripple(QPoint(10+t, 20+t));
    ripple->setColor(d->track->trackColor());
    ripple->setRadiusEndValue(w);
    ripple->setOpacityStartValue(0.8);

    d->ripple->addRipple(ripple);
}

bool Toggle::event(QEvent *event)
{
    Q_D(Toggle);

    switch (event->type())
    {
    case QEvent::EnabledChange:
        if (isEnabled()) {
            d->machine->start();
        } else {
            d->machine->stop();
        }
        break;
    case QEvent::ParentChange:
        QWidget *widget;
        if ((widget = parentWidget())) {
            d->ripple->setParent(widget);
        }
        break;
    case QEvent::Resize:
    case QEvent::Move:
        d->ripple->setGeometry(geometry().adjusted(-10, -20, 10, 20));
        break;
    default:
        break;
    }
    return QAbstractButton::event(event);
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

#ifdef DEBUG_LAYOUT
    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setOpacity(1);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
}
