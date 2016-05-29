#include "toggle.h"
#include <QPainter>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QDebug>
#include "lib/rippleoverlay.h"
#include "lib/ripple.h"
#include "lib/style.h"
#include "toggle_p.h"
#include "toggle_internal.h"

TogglePrivate::TogglePrivate(Toggle *q)
    : q_ptr(q),
      track(new ToggleTrack(q)),
      thumb(new ToggleThumb(q)),
      orientation(Qt::Horizontal)
{
}

void TogglePrivate::init()
{
    Q_Q(Toggle);

    ripple = new RippleOverlay(q->parentWidget());

    q->setCheckable(true);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QState *offState = new QState;
    QState *onState = new QState;

    machine.addState(offState);
    machine.addState(onState);

    machine.setInitialState(offState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QSignalTransition(thumb, SIGNAL(clicked(bool)));
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation;
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    transition = new QSignalTransition(thumb, SIGNAL(clicked(bool)));
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation;
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    const Style &style = Style::instance();

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    QColor trackOnColor = style.themeColor("primary1");
    trackOnColor.setAlpha(100);

    QColor trackOffColor = style.themeColor("accent3");
    trackOffColor.setAlpha(170);

    offState->assignProperty(track, "trackColor", trackOffColor);
    onState->assignProperty(track, "trackColor", trackOnColor);

    offState->assignProperty(thumb, "thumbColor", style.themeColor("canvas"));
    onState->assignProperty(thumb, "thumbColor", style.themeColor("primary1"));

    machine.start();

    QObject::connect(thumb, SIGNAL(clicked(bool)), q, SLOT(addRipple(bool)));
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

void Toggle::addRipple(bool checked)
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
    ripple->setColor(Style::instance().themeColor(checked
          ? "primary2"
          : "accent3"));
    ripple->setRadiusEndValue(w);
    ripple->setOpacityStartValue(0.4);

    d->ripple->addRipple(ripple);
}

bool Toggle::event(QEvent *event)
{
    Q_D(Toggle);

    const QEvent::Type type = event->type();

    if (QEvent::EnabledChange == type) {
        if (isEnabled()) {
            d->machine.start();
        } else {
            d->machine.stop();
        }
    } else if (QEvent::ParentChange == type && parentWidget()) {
        d->ripple->setParent(parentWidget());
    } else if (QEvent::Resize == type || QEvent::Move == type) {
        d->ripple->setGeometry(geometry().adjusted(-10, -20, 10, 20));
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
