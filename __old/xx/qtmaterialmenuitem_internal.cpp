#include "xx/qtmaterialmenuitem_internal.h"
#include <QSignalTransition>
#include <QPropertyAnimation>

/*!
 *  \class QtMaterialMenuItemStateMachine
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialMenuItemStateMachine::QtMaterialMenuItemStateMachine(QtMaterialMenuItem *menuItem)
    : QStateMachine(menuItem),
      m_menuItem(menuItem),
      m_defaultState(new QState),
      m_highlightedState(new QState)
{
    Q_ASSERT(menuItem);

    addState(m_defaultState);
    addState(m_highlightedState);

    setInitialState(m_defaultState);

    QSignalTransition *transition;

    transition = new QSignalTransition(this, SIGNAL(highlight()));
    transition->setTargetState(m_highlightedState);
    m_defaultState->addTransition(transition);

    transition = new QSignalTransition(this, SIGNAL(unhighlight()));
    transition->setTargetState(m_defaultState);
    m_highlightedState->addTransition(transition);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);
    animation->setPropertyName("foregroundColor");
    animation->setDuration(160);
    addDefaultAnimation(animation);
}

/*!
 *  \internal
 */
QtMaterialMenuItemStateMachine::~QtMaterialMenuItemStateMachine()
{
}
