#include "raisedbutton.h"
#include <QGraphicsDropShadowEffect>
#include <QEventTransition>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOption>
#include <QMouseEvent>
#include <QDebug>
#include "raisedbutton_p.h"

void RaisedButtonPrivate::init()
{
    Q_Q(RaisedButton);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(7);
    effect->setOffset(QPointF(0, 0));
    effect->setColor(QColor(0, 0, 0, 60));
    q->setGraphicsEffect(effect);

    QState *normalState = new QState;
    QState *pressedState = new QState;

    machine.addState(normalState);
    machine.addState(pressedState);

    normalState->assignProperty(effect, "offset", QPointF(0, 0));
    normalState->assignProperty(effect, "blurRadius", 7);

    pressedState->assignProperty(effect, "offset", QPointF(0, 6));
    pressedState->assignProperty(effect, "blurRadius", 20);

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QEventTransition(q, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);

    animation = new QPropertyAnimation(effect, "offset");
    animation->setDuration(100);
    transition->addAnimation(animation);
    animation = new QPropertyAnimation(effect, "blurRadius");
    animation->setDuration(100);
    transition->addAnimation(animation);

    normalState->addTransition(transition);

    //

    transition = new QEventTransition(q, QEvent::MouseButtonDblClick);
    transition->setTargetState(pressedState);

    animation = new QPropertyAnimation(effect, "offset");
    animation->setDuration(100);
    transition->addAnimation(animation);
    animation = new QPropertyAnimation(effect, "blurRadius");
    animation->setDuration(100);
    transition->addAnimation(animation);

    normalState->addTransition(transition);

    //

    transition = new QEventTransition(q, QEvent::MouseButtonRelease);
    transition->setTargetState(normalState);

    animation = new QPropertyAnimation(effect, "offset");
    transition->addAnimation(animation);
    animation->setDuration(100);
    animation = new QPropertyAnimation(effect, "blurRadius");
    animation->setDuration(100);
    transition->addAnimation(animation);

    pressedState->addTransition(transition);

    //

    machine.setInitialState(normalState);
    machine.start();
}

RaisedButton::RaisedButton(QWidget *parent)
    : FlatButton(*new RaisedButtonPrivate(this), parent)
{
    Q_D(RaisedButton);

    d->init();

    setMinimumHeight(42);
}

RaisedButton::~RaisedButton()
{
}

void RaisedButton::setRole(Material::Role role)
{
    Q_D(FlatButton);

    d->role = role;

    switch (role)
    {
    case Material::Primary:
        d->setPaletteColor(QPalette::Active, QPalette::Background, "primary1");
        d->setPaletteColor(QPalette::Active, QPalette::ButtonText, "alternateText");
        break;
    case Material::Secondary:
        d->setPaletteColor(QPalette::Active, QPalette::Background, "accent1");
        d->setPaletteColor(QPalette::Active, QPalette::ButtonText, "alternateText");
        break;
    default:
        d->setPaletteColor(QPalette::Active, QPalette::Background, "canvas");
        d->setPaletteColor(QPalette::Active, QPalette::ButtonText, "text");
        break;
    }
    d->delegate->assignProperties();
    update();
}

void RaisedButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(RaisedButton);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(palette().color(QPalette::Active, QPalette::Background));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(rect(), 3, 3);

    QStylePainter style(this);

    QStyleOptionButton option;
    initStyleOption(&option);
    option.features |= QStyleOptionButton::Flat;

    style.drawControl(QStyle::CE_PushButtonLabel, option);
}
