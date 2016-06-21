#include "snackbar_internal.h"
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QTimer>
#include "snackbar.h"

SnackbarStateMachine::SnackbarStateMachine(Snackbar *parent)
    : QStateMachine(parent),
      snackbar(parent),
      _offset(0)
{
    _timer.setSingleShot(true);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;
    QState *finalState = new QState;

    addState(hiddenState);
    addState(visibleState);
    addState(finalState);

    setInitialState(hiddenState);

    QSignalTransition *transition;

    transition = new QSignalTransition(this, SIGNAL(showSnackbar()));
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(hideSnackbar()));
    transition->setTargetState(visibleState);
    hiddenState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(hideSnackbar()));
    transition->setTargetState(finalState);
    visibleState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(waitForSnackbar()));
    transition->setTargetState(hiddenState);
    finalState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(showNextSnackbar()));
    transition->setTargetState(visibleState);
    finalState->addTransition(transition);

    connect(visibleState, SIGNAL(propertiesAssigned()),
            this, SLOT(snackbarShown()));
    connect(finalState, SIGNAL(propertiesAssigned()),
            this, SLOT(snackbarHidden()));

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this, "offset", this);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setDuration(400);
    addDefaultAnimation(animation);

    hiddenState->assignProperty(this, "offset", 1);
    visibleState->assignProperty(this, "offset", 0);
    finalState->assignProperty(this, "offset", 1);

    connect(&_timer, SIGNAL(timeout()), this, SIGNAL(hideSnackbar()));
    connect(this, SIGNAL(hideSnackbar()), &_timer, SLOT(stop()));
}

SnackbarStateMachine::~SnackbarStateMachine()
{
}

void SnackbarStateMachine::setOffset(qreal offset)
{
    _offset = offset;
    snackbar->update();
}

qreal SnackbarStateMachine::offset() const
{
    return _offset;
}

void SnackbarStateMachine::snackbarHidden()
{
    snackbar->dequeue();
}

void SnackbarStateMachine::snackbarShown()
{
    _timer.start(snackbar->autoHideDuration());
}
