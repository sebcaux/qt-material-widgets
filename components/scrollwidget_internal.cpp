#include "scrollwidget_internal.h"
#include <QPropertyAnimation>
#include <QEventTransition>

ScrollBarStateMachine::ScrollBarStateMachine(ScrollBar *parent)
    : QStateMachine(parent),
      scrollBar(parent),
      _opacity(0)
{
    QState *focusState = new QState;
    QState *blurState = new QState;

    addState(focusState);
    addState(blurState);

    setInitialState(blurState);

    QEventTransition *transition;

    //

    transition = new QEventTransition(parent, QEvent::HoverEnter);
    transition->setTargetState(focusState);

    blurState->addTransition(transition);

    //

    transition = new QEventTransition(parent, QEvent::HoverLeave);
    transition->setTargetState(blurState);

    focusState->addTransition(transition);

    //

    focusState->assignProperty(this, "opacity", 1);
    blurState->assignProperty(this, "opacity", 0);

    //

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(340);

    addDefaultAnimation(animation);
}

ScrollBarStateMachine::~ScrollBarStateMachine()
{
}
