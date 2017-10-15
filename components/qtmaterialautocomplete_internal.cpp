#include "qtmaterialautocomplete_internal.h"
#include <QPropertyAnimation>

/*!
 *  \class QtMaterialAutoCompleteStateMachine
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAutoCompleteStateMachine::QtMaterialAutoCompleteStateMachine(QtMaterialAutoComplete *parent)
    : QStateMachine(parent),
      m_autoComplete(parent),
      m_closedState(new QState),
      m_openState(new QState),
      m_closingState(new QState)
{
    Q_ASSERT(parent);

    addState(m_closedState);
    addState(m_openState);
    addState(m_closingState);
    setInitialState(m_closedState);

    QEventTransition *transition;

    //transition = new QEventTransition(parent, QEvent::HoverEnter);
    //transition->setTargetState(m_focusState);
    //m_blurState->addTransition(transition);
}

/*!
 *  \internal
 */
QtMaterialAutoCompleteStateMachine::~QtMaterialAutoCompleteStateMachine()
{
}
