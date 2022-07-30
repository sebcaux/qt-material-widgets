#ifndef QTMATERIALMENU_H
#define QTMATERIALMENU_H

#include <QtWidgets/QWidget>

class QtMaterialMenu : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialMenu(QWidget *parent = nullptr);
    ~QtMaterialMenu() override;
};

#endif  // QTMATERIALMENU_H
