#include "drawer_internal.h"
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "drawer.h"

DrawerStateMachine::DrawerStateMachine(Drawer *drawer)
    : QStateMachine(drawer),
      m_drawer(drawer),
      m_openState(new QState),
      m_closedState(new QState),
      m_offset(0)
{
    addState(m_openState);
    addState(m_closedState);

    setInitialState(m_closedState);

    QSignalTransition *transition;
    QPropertyAnimation *animation;

    transition = new QSignalTransition(this, SIGNAL(enterOpenedState()));
    transition->setTargetState(m_openState);
    m_closedState->addTransition(transition);

    animation = new QPropertyAnimation(this, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    transition->addAnimation(animation);

    transition = new QSignalTransition(this, SIGNAL(enterClosedState()));
    transition->setTargetState(m_closedState);
    m_openState->addTransition(transition);

    animation = new QPropertyAnimation(this, "offset", this);
    animation->setDuration(220);
    animation->setEasingCurve(QEasingCurve::InCirc);
    transition->addAnimation(animation);

    updatePropertyAssignments();
}

DrawerStateMachine::~DrawerStateMachine()
{
}

void DrawerStateMachine::setOffset(int offset)
{
    m_offset = offset;

    QWidget *widget = m_drawer->parentWidget();
    if (widget) {
        m_drawer->setGeometry(widget->rect().translated(offset, 0));
    }
}

void DrawerStateMachine::updatePropertyAssignments()
{
    m_closedState->assignProperty(this, "offset", -(m_drawer->width()+32));
    m_openState->assignProperty(this, "offset", 0);
}
