#ifndef QTMATERIALMENUITEM_P_H
#define QTMATERIALMENUITEM_P_H

#include "xx/qtmaterialflatbutton_p.h"

class QtMaterialMenuItem;
class QtMaterialMenuItemStateMachine;

class QtMaterialMenuItemPrivate : public QtMaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialMenuItemPrivate)
    Q_DECLARE_PUBLIC(QtMaterialMenuItem)

public:
    QtMaterialMenuItemPrivate(QtMaterialMenuItem *q);
    ~QtMaterialMenuItemPrivate();

    void init();

    bool highlighted;
};

#endif // QTMATERIALMENUITEM_P_H
