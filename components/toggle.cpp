#include "toggle.h"
#include <QPainter>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "lib/rippleoverlay.h"
#include "toggle_p.h"

TogglePrivate::TogglePrivate(Toggle *q)
    : q_ptr(q),
      thumb(new Thumb(q)),
      ripple(new RippleOverlay(q->parentWidget())),
      orientation(Qt::Horizontal)
{
}

void TogglePrivate::init()
{
    Q_Q(Toggle);

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

    transition = new QSignalTransition(thumb, SIGNAL(clicked()));
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation;
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    transition = new QSignalTransition(thumb, SIGNAL(clicked()));
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation;
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    //

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    machine.start();

    QObject::connect(thumb, SIGNAL(clicked()), q, SLOT(addRipple()));
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

void Toggle::addRipple()
{
    Q_D(Toggle);

    if (Qt::Horizontal == d->orientation) {
        const int t = height()/2;
        const int w = d->thumb->height()/2+10;
        d->ripple->addRipple(QPoint(10+t, 20+t), w);
    } else {
        const int t = width()/2;
        const int w = d->thumb->width()/2+10;
        d->ripple->addRipple(QPoint(10+t, 20+t), w);
    }
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

    Q_D(Toggle);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == d->orientation) {
        const int h = height()/2;
        const QRect r(0, h/2, width(), h);
        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
    } else {
        const int w = width()/2;
        const QRect r(w/2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w/2-4, w/2-4);
    }
}
