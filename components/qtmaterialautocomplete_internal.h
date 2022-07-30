#ifndef QTMATERIALAUTOCOMPLETESTATEMACHINE_H
#define QTMATERIALAUTOCOMPLETESTATEMACHINE_H

#include "qtmaterialautocomplete.h"
#include <QStateMachine>

class QtMaterialAutoCompleteStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit QtMaterialAutoCompleteStateMachine(QWidget *menu);
    ~QtMaterialAutoCompleteStateMachine() override;

signals:
    void shouldOpen();
    void shouldClose();
    void shouldFade();

private:
    Q_DISABLE_COPY(QtMaterialAutoCompleteStateMachine)

    QWidget *const m_menu;
    QState *const m_closedState;
    QState *const m_openState;
    QState *const m_closingState;
};

#endif  // QTMATERIALAUTOCOMPLETESTATEMACHINE_H
