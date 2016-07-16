#ifndef QTMATERIALCHECKABLE_P_H
#define QTMATERIALCHECKABLE_P_H

#include <QtGlobal>

class QtMaterialCheckable;
class QtMaterialRippleOverlay;
class QtMaterialCheckableIcon;

class QtMaterialCheckablePrivate
{
    Q_DISABLE_COPY(QtMaterialCheckablePrivate)
    Q_DECLARE_PUBLIC(QtMaterialCheckable)

public:
    QtMaterialCheckablePrivate(QtMaterialCheckable *q);
    virtual ~QtMaterialCheckablePrivate();

    void init();

    QtMaterialCheckable     *const q_ptr;
    QtMaterialRippleOverlay *rippleOverlay;
    QtMaterialCheckableIcon *checkedIcon;
    QtMaterialCheckableIcon *uncheckedIcon;
};

#endif // QTMATERIALCHECKABLE_P_H
