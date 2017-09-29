#ifndef QTMATERIALICONMENU_P_H
#define QTMATERIALICONMENU_P_H

#include "xx/qtmaterialiconbutton_p.h"

class QtMaterialIconMenu;
class QtMaterialOverlayWidget;
class QtMaterialCollapsibleMenu;

class QtMaterialIconMenuPrivate : public QtMaterialIconButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialIconMenuPrivate)
    Q_DECLARE_PUBLIC(QtMaterialIconMenu)

public:
    QtMaterialIconMenuPrivate(QtMaterialIconMenu *q);
    ~QtMaterialIconMenuPrivate();

    void init();

    QtMaterialOverlayWidget   *menuOverlay;
    QtMaterialCollapsibleMenu *menu;
    bool                       autoCollapse;
};

#endif // QTMATERIALICONMENU_P_H
