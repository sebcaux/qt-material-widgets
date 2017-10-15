#ifndef QTMATERIALAUTOCOMPLETESTATEMACHINE_H
#define QTMATERIALAUTOCOMPLETESTATEMACHINE_H

#include <QStateMachine>
#include "qtmaterialautocomplete.h"

class QtMaterialAutoCompleteStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    QtMaterialAutoCompleteStateMachine(QtMaterialAutoComplete *parent);
    ~QtMaterialAutoCompleteStateMachine();

private:
    Q_DISABLE_COPY(QtMaterialAutoCompleteStateMachine)

    QtMaterialAutoComplete *const m_autoComplete;
    QState                 *m_closedState;
    QState                 *m_openState;
    QState                 *m_closingState;
};

#endif // QTMATERIALAUTOCOMPLETESTATEMACHINE_H
