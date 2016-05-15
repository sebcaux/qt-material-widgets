#include "flatbutton_internal.h"
#include <QAbstractTransition>
#include <QEventTransition>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "flatbutton.h"
#include "lib/style.h"

FlatButtonDelegate::FlatButtonDelegate(FlatButton *parent)
    : QStateMachine(parent),
      button(parent)
{
    Style &style = Style::instance();

    QState *normalState = new QState;
    QState *focusedState = new QState;
    QState *pressedState = new QState;

    addState(normalState);
    addState(focusedState);
    addState(pressedState);

    setInitialState(normalState);

    normalState->assignProperty(this, "backgroundOpacity", 0);
    normalState->assignProperty(this, "backgroundColor", style.themeColor("text"));

    focusedState->assignProperty(this, "backgroundOpacity", 0.15);
    focusedState->assignProperty(this, "backgroundColor", style.themeColor("text"));

    pressedState->assignProperty(this, "backgroundOpacity", 0.15);
    pressedState->assignProperty(this, "backgroundColor", style.themeColor("text"));

    QAbstractTransition *transition;
    QPropertyAnimation *animation;

    //

    transition = new QEventTransition(button, QEvent::Enter);
    transition->setTargetState(focusedState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(140);
    transition->addAnimation(animation);
    normalState->addTransition(transition);

    //

    transition = new QEventTransition(button, QEvent::Leave);
    transition->setTargetState(normalState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(140);
    transition->addAnimation(animation);
    focusedState->addTransition(transition);

    //

    transition = new QEventTransition(button, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(140);
    transition->addAnimation(animation);
    focusedState->addTransition(transition);

    //

    transition = new QEventTransition(button, QEvent::MouseButtonRelease);
    transition->setTargetState(focusedState);

    animation = new QPropertyAnimation(this, "backgroundOpacity");
    animation->setDuration(500);
    transition->addAnimation(animation);
    pressedState->addTransition(transition);

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
