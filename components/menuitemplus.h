#ifndef MENUITEMPLUS_H
#define MENUITEMPLUS_H

#include "xx/qtmaterialflatbutton.h"

class MenuItemPlus : public QtMaterialFlatButton
{
    Q_OBJECT

public:
    explicit MenuItemPlus(QWidget *parent = 0);
    ~MenuItemPlus();

protected:
    void paintForeground(QPainter *painter) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(MenuItemPlus)
    //Q_DECLARE_PRIVATE(MenuItemPlus)
};

#endif // MENUITEMPLUS_H
