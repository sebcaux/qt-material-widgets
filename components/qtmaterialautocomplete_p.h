#ifndef QTMATERIALAUTOCOMPLETE_P_H
#define QTMATERIALAUTOCOMPLETE_P_H

#include "qtmaterialtextfield_p.h"

class QWidget;
class QVBoxLayout;
class QtMaterialAutoCompleteOverlay;
class QtMaterialAutoCompleteStateMachine;

class QtMaterialAutoCompletePrivate : public QtMaterialTextFieldPrivate
{
    Q_DISABLE_COPY(QtMaterialAutoCompletePrivate)
    Q_DECLARE_PUBLIC(QtMaterialAutoComplete)

public:
    QtMaterialAutoCompletePrivate(QtMaterialAutoComplete *q);
    virtual ~QtMaterialAutoCompletePrivate();

    void init();

    QtMaterialAutoCompleteStateMachine *stateMachine;
    QWidget                            *menu;
    QVBoxLayout                        *menuLayout;
    QStringList                         dataSource;
    int                                 maxWidth;
};

#endif // QTMATERIALAUTOCOMPLETE_P_H
