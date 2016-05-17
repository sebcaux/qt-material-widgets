#include "raisedbutton.h"
#include <QGraphicsDropShadowEffect>
#include <QEventTransition>
#include "raisedbutton_p.h"

void RaisedButtonPrivate::init()
{
    Q_Q(RaisedButton);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(7);
    effect->setOffset(QPoint(0, 0));
    effect->setColor(QColor(0, 0, 0, 100));
    q->setGraphicsEffect(effect);

    q->setAutoFillBackground(true);

    QState *normalState = new QState;
    QState *pressedState = new QState;

    machine.addState(normalState);
    machine.addState(pressedState);

    normalState->assignProperty(effect, "offset", QPoint(0, 0));
    normalState->assignProperty(effect, "blurRadius", 7);

    pressedState->assignProperty(effect, "offset", QPoint(0, 6));
    pressedState->assignProperty(effect, "blurRadius", 20);

    QAbstractTransition *transition;

    transition = new QEventTransition(q, QEvent::MouseButtonPress);
    transition->setTargetState(pressedState);
    normalState->addTransition(transition);

    transition = new QEventTransition(q, QEvent::MouseButtonRelease);
    transition->setTargetState(normalState);
    pressedState->addTransition(transition);

    machine.setInitialState(normalState);

    // add animation.. duration: 100 !!!

    machine.start();
}

RaisedButton::RaisedButton(QWidget *parent)
    : FlatButton(*new RaisedButtonPrivate(this), parent)
{
    Q_D(RaisedButton);

    d->init();
}

RaisedButton::~RaisedButton()
{
}
