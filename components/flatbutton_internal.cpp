#include "flatbutton_internal.h"
#include <QAbstractTransition>
#include <QEventTransition>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "flatbutton.h"
#include "lib/style.h"

FlatButtonDelegate::FlatButtonDelegate(FlatButton *parent)
    : QStateMachine(parent),
      button(parent),
      _normalState(new QState(this)),
      _focusedState(new QState(this)),
      _pressedState(new QState(this))
{
    setInitialState(_normalState);

    assignProperties();

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QEventTransition(button, QEvent::Enter);
    transition->setTargetState(_focusedState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(140);
    transition->addAnimation(animation);
    _normalState->addTransition(transition);

    //

    transition = new QEventTransition(button, QEvent::Leave);
    transition->setTargetState(_normalState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(140);
    transition->addAnimation(animation);
    _focusedState->addTransition(transition);

    //

    transition = new QEventTransition(button, QEvent::MouseButtonPress);
    transition->setTargetState(_pressedState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(140);
    transition->addAnimation(animation);
    _focusedState->addTransition(transition);

    //

    transition = new QEventTransition(button, QEvent::MouseButtonRelease);
    transition->setTargetState(_focusedState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(500);
    transition->addAnimation(animation);
    _pressedState->addTransition(transition);

    //

    start();
}

FlatButtonDelegate::~FlatButtonDelegate()
{
}

void FlatButtonDelegate::setBackgroundOpacity(qreal opacity)
{
    _backgroundOpacity = opacity;
    button->update();
}

qreal FlatButtonDelegate::backgroundOpacity() const
{
    return _backgroundOpacity;
}

void FlatButtonDelegate::setBackgroundColor(const QColor &color)
{
    _backgroundColor = color;
    button->update();
}

QColor FlatButtonDelegate::backgroundColor() const
{
    return _backgroundColor;
}

void FlatButtonDelegate::assignProperties()
{
    QColor textColor = button->palette().color(QPalette::Active,
                                               QPalette::ButtonText);

    _normalState->assignProperty(this, "backgroundOpacity", 0);
    _normalState->assignProperty(this, "backgroundColor", textColor);

    _focusedState->assignProperty(this, "backgroundOpacity", 0.15);
    _focusedState->assignProperty(this, "backgroundColor", textColor);

    _pressedState->assignProperty(this, "backgroundOpacity", 0.15);
    _pressedState->assignProperty(this, "backgroundColor", textColor);
}
