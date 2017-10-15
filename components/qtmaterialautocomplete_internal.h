#ifndef QTMATERIALAUTOCOMPLETESTATEMACHINE_H
#define QTMATERIALAUTOCOMPLETESTATEMACHINE_H

#include <QStateMachine>
#include "qtmaterialautocomplete.h"

class QtMaterialAutoCompleteStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit QtMaterialAutoCompleteStateMachine(QWidget *menu);
    ~QtMaterialAutoCompleteStateMachine();

signals:
    void shouldOpen();
    void shouldClose();
    void shouldFade();

private:
    Q_DISABLE_COPY(QtMaterialAutoCompleteStateMachine)

    QWidget *const m_menu;
    QState  *m_closedState;
    QState  *m_openState;
    QState  *m_closingState;
};

#endif // QTMATERIALAUTOCOMPLETESTATEMACHINE_H
