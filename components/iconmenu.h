#ifndef ICONMENU_H
#define ICONMENU_H

#include <QWidget>

class IconMenu : public QWidget
{
    Q_OBJECT

public:
    explicit IconMenu(QWidget *parent = 0);
    ~IconMenu();
};

#endif // ICONMENU_H
