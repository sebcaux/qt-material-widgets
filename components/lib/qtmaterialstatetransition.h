#ifndef QTMATERIALSTATETRANSITION_H
#define QTMATERIALSTATETRANSITION_H

#include <QAbstractTransition>

#include "lib/qtmaterialstatetransitionevent.h"

class QtMaterialStateTransition : public QAbstractTransition
{
    Q_OBJECT

public:
    QtMaterialStateTransition(QtMaterialStateTransitionType type);

protected:
    bool eventTest(QEvent *event) override;
    void onTransition(QEvent * /*event*/) override;

private:
    QtMaterialStateTransitionType m_type;
};

#endif  // QTMATERIALSTATETRANSITION_H
