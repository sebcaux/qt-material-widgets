#ifndef ICONMENU_H
#define ICONMENU_H

#include <QWidget>
#include "iconbutton.h"

class Menu;

class MenuOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit MenuOverlay(QWidget *parent = 0);
    ~MenuOverlay();
};

class IconMenu : public IconButton
{
    Q_OBJECT

public:
    explicit IconMenu(const QIcon &icon, QWidget *parent = 0);
    ~IconMenu();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;

private:
    MenuOverlay   *const _menuOverlay;
    Menu          *const _menu;
    QWidget       *_menuGeometryWidget;
};

#endif // ICONMENU_H
