#include "raisedbutton.h"
#include "raisedbutton_p.h"
#include <QGraphicsDropShadowEffect>
#include <QEventTransition>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QDebug>
#include <QStylePainter>
#include <QStyleOption>
#include <QMouseEvent>

RaisedButtonPrivate::RaisedButtonPrivate(RaisedButton *q)
    : FlatButtonPrivate(q),
      machine(new QStateMachine),
      normalState(new QState),
      pressedState(new QState),
      effect(new QGraphicsDropShadowEffect)
{
    qDebug() << "RaisedButtonPrivate";
}

RaisedButtonPrivate::~RaisedButtonPrivate()
{
}

void RaisedButtonPrivate::init()
{
    Q_Q(RaisedButton);

    machine->setParent(q);

    q->setTextColor(Qt::white);
    q->setPeakOpacity(0.25);

    effect->setBlurRadius(7);
    effect->setOffset(QPointF(0, 2));
    effect->setColor(QColor(0, 0, 0, 60));
    q->setGraphicsEffect(effect);

    machine->addState(normalState);
    machine->addState(pressedState);

    normalState->assignProperty(effect, "offset", QPointF(0, 2));
    normalState->assignProperty(effect, "blurRadius", 7);

    pressedState->assignProperty(effect, "offset", QPointF(0, 6));
    pressedState->assignProperty(effect, "blurRadius", 20);

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QEventTransition(q, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);

    animation = new QPropertyAnimation(effect, "offset", q);
    animation->setDuration(100);
    transition->addAnimation(animation);
    animation = new QPropertyAnimation(effect, "blurRadius", q);
    animation->setDuration(100);
    transition->addAnimation(animation);

    normalState->addTransition(transition);

    //

    transition = new QEventTransition(q, QEvent::MouseButtonDblClick);
    transition->setTargetState(pressedState);

    animation = new QPropertyAnimation(effect, "offset", q);
    animation->setDuration(100);
    transition->addAnimation(animation);
    animation = new QPropertyAnimation(effect, "blurRadius", q);
    animation->setDuration(100);
    transition->addAnimation(animation);

    normalState->addTransition(transition);

    //

    transition = new QEventTransition(q, QEvent::MouseButtonRelease);
    transition->setTargetState(normalState);

    animation = new QPropertyAnimation(effect, "offset", q);
    transition->addAnimation(animation);
    animation->setDuration(100);
    animation = new QPropertyAnimation(effect, "blurRadius", q);
    animation->setDuration(100);
    transition->addAnimation(animation);

    pressedState->addTransition(transition);

    //

    machine->setInitialState(normalState);
    machine->start();
}

RaisedButton::RaisedButton(QWidget *parent)
    : FlatButton(*new RaisedButtonPrivate(this), parent)
{
    qDebug() << "RaisedButton::RaisedButton";

    d_func()->init();

    setMinimumHeight(42);
}

RaisedButton::~RaisedButton()
{
}

void RaisedButton::setDisabledBackgroundColor(const QColor &color)
{
    Q_D(RaisedButton);

    d->disabledBackgroundColor = color;
    setUseThemeColors(false);
}

QColor RaisedButton::disabledBackgroundColor() const
{
    Q_D(const RaisedButton);

    if (d->useThemeColors || !d->disabledBackgroundColor.isValid()) {
        return Style::instance().themeColor("disabled3");
    } else {
        return d->disabledBackgroundColor;
    }
}

RaisedButton::RaisedButton(RaisedButtonPrivate &d, QWidget *parent)
    : FlatButton(d, parent)
{
    d_func()->init();
}

bool RaisedButton::event(QEvent *event)
{
    Q_D(RaisedButton);

    if (QEvent::EnabledChange == event->type()) {
        if (isEnabled()) {
            d->machine->start();
            d->effect->setEnabled(true);
        } else {
            d->machine->stop();
            d->effect->setEnabled(false);
        }
    }
    return FlatButton::event(event);
}

void RaisedButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(RaisedButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();

    const qreal cr = d->cornerRadius;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled()
       ? backgroundColor()
       : disabledBackgroundColor());
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), cr, cr);

    if (isEnabled()) {
        const qreal s = d->delegate->haloScaleFactor()*d->delegate->haloSize()*0.7;
        const qreal hs = static_cast<qreal>(width())*s;
        const qreal haloOpacity = d->delegate->haloOpacity();

        brush.setColor(palette().color(QPalette::Active, QPalette::ButtonText));
        painter.setBrush(brush);
        painter.setOpacity(haloOpacity);
        painter.setPen(Qt::NoPen);
        QPointF center = rect().center();
        painter.drawEllipse(center, hs, hs);
    }

    painter.restore();

    QStylePainter style(this);

    QStyleOptionButton option;
    initStyleOption(&option);
    option.features |= QStyleOptionButton::Flat;

    style.drawControl(QStyle::CE_PushButtonLabel, option);
}
