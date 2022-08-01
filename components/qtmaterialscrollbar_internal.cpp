#include "qtmaterialscrollbar_internal.h"

#include <QEventTransition>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QTimer>

#include "lib/qtmaterialstatetransition.h"

/*!
 *  \class QtMaterialScrollBarStateMachine
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialScrollBarStateMachine::QtMaterialScrollBarStateMachine(QtMaterialScrollBar *parent)
    : QStateMachine(parent),
      m_scrollBar(parent),
      m_focusState(new QState),
      m_scrollState(new QState),
      m_blurState(new QState),
      m_scrollOutTimer(new QTimer),
      m_opacity(0)
{
    Q_ASSERT(parent);

    m_scrollOutTimer->setSingleShot(true);

    addState(m_focusState);
    addState(m_scrollState);
    addState(m_blurState);
    setInitialState(m_blurState);

    QEventTransition *transitionEnter = new QEventTransition(parent, QEvent::Enter);
    transitionEnter->setTargetState(m_focusState);
    m_blurState->addTransition(transitionEnter);

    QEventTransition *transitionLeave = new QEventTransition(parent, QEvent::Leave);
    transitionLeave->setTargetState(m_blurState);
    m_focusState->addTransition(transitionLeave);

    QtMaterialStateTransition *transitionScroll = new QtMaterialStateTransition(ScrollbarValueMoved);
    transitionScroll->setTargetState(m_scrollState);
    m_blurState->addTransition(transitionScroll);
    connect(m_scrollState, &QState::entered, m_scrollOutTimer, [=]{m_scrollOutTimer->start(600);});

    QSignalTransition *transitionScrollout = new QSignalTransition(m_scrollOutTimer, &QTimer::timeout);
    transitionScrollout->setTargetState(m_blurState);
    m_scrollState->addTransition(transitionScrollout);

    QEventTransition *transitionEnterFromScroll = new QEventTransition(parent, QEvent::Enter);
    transitionEnterFromScroll->setTargetState(m_focusState);
    m_scrollState->addTransition(transitionEnterFromScroll);

    startTimer(1);

    m_focusState->assignProperty(this, "opacity", 1);
    m_scrollState->assignProperty(this, "opacity", 1);
    m_blurState->assignProperty(this, "opacity", 0);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(340);
    addDefaultAnimation(animation);
}

/*!
 *  \internal
 */
QtMaterialScrollBarStateMachine::~QtMaterialScrollBarStateMachine()
{
}
