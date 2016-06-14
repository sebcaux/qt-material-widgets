#include "textfield_internal.h"
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QDebug>
#include "textfield.h"

TextFieldStateMachine::TextFieldStateMachine(TextField *parent)
    : QStateMachine(parent),
      textField(parent),
      _progress(0)
{
    QState *normalState = new QState;
    QState *focusedState = new QState;

    addState(normalState);
    addState(focusedState);

    setInitialState(normalState);

    QEventTransition *transition;
    QPropertyAnimation *animation;

    transition = new QEventTransition(parent, QEvent::FocusIn);
    transition->setTargetState(focusedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(parent, QEvent::FocusOut);
    transition->setTargetState(normalState);
    focusedState->addTransition(transition);

    normalState->assignProperty(this, "progress", 0);
    focusedState->assignProperty(this, "progress", 1);

    animation = new QPropertyAnimation(this, "progress");
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->setDuration(340);
    addDefaultAnimation(animation);
}

TextFieldStateMachine::~TextFieldStateMachine()
{
}

void TextFieldStateMachine::setProgress(qreal progress)
{
    _progress = progress;
    textField->update();
}
