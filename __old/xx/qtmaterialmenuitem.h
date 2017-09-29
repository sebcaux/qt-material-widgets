#ifndef QTMATERIALMENUITEM_H
#define QTMATERIALMENUITEM_H

#include "xx/qtmaterialflatbutton.h"

class QtMaterialMenuItemPrivate;

class QtMaterialMenuItem : public QtMaterialFlatButton
{
    Q_OBJECT

public:
    explicit QtMaterialMenuItem(QWidget *parent = 0);
    ~QtMaterialMenuItem();

    void setHighlighted(bool value);
    bool isHighlighted() const;

protected:
    void paintForeground(QPainter *painter) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialMenuItem)
    Q_DECLARE_PRIVATE(QtMaterialMenuItem)
};

#endif // QTMATERIALMENUITEM_H
