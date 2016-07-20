#include "xx/qtmaterialsnackbar_internal.h"
#include "xx/qtmaterialsnackbar.h"

QtMaterialSnackbarStateMachine::QtMaterialSnackbarStateMachine(QtMaterialSnackbar *parent)
    : QStateMachine(parent),
      m_snackbar(parent)
{
    m_timer.setSingleShot(true);

    QState *hiddenState = new QState;
    QState *visibleState = new QState;
    QState *finalState = new QState;

    addState(hiddenState);
    addState(visibleState);
    addState(finalState);

    setInitialState(hiddenState);

    QSignalTransition *transition;

    //

    //
}

QtMaterialSnackbarStateMachine::~QtMaterialSnackbarStateMachine()
{
}

void QtMaterialSnackbarStateMachine::setOffset(qreal offset)
{
    m_offset = offset;
    m_snackbar->update();
}
