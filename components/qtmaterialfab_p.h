#ifndef QTMATERIALFAB_P_H
#define QTMATERIALFAB_P_H

#include "qtmaterialflatbutton_p.h"

#include "qtmaterialfab.h"

class QtMaterialFloatingActionButton;

class QtMaterialFloatingActionButtonPrivate : public QtMaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialFloatingActionButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialFloatingActionButton)

public:
    enum
    {
        DefaultDiameter = 56,
        MiniDiameter = 40
    };

    enum
    {
        DefaultIconSize = 24,
        MiniIconSize = 18
    };

    QtMaterialFloatingActionButtonPrivate(QtMaterialFloatingActionButton *q);
    ~QtMaterialFloatingActionButtonPrivate() override;

    void init();
    QRect fabGeometry() const;
    void setupProperties();

    inline int diameter() const;
    inline int iconSize() const;

    Qt::Corner corner;
    bool mini;
    QPoint offset;
};

inline int QtMaterialFloatingActionButtonPrivate::diameter() const
{
    return mini ? MiniDiameter : DefaultDiameter;
}

inline int QtMaterialFloatingActionButtonPrivate::iconSize() const
{
    return mini ? MiniIconSize : DefaultIconSize;
}

#endif  // QTMATERIALFAB_P_H
