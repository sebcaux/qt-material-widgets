#ifndef QTMATERIALAPPBAR_P_H
#define QTMATERIALAPPBAR_P_H

#include "lib/qtmaterialtheme.h"
#include "qtmaterialiconbutton.h"

#include <QColor>
#include <QLabel>

class QtMaterialAppBar;
class QtMaterialAppBarLayout;

class QtMaterialAppBarPrivate
{
    Q_DISABLE_COPY(QtMaterialAppBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialAppBar)

public:
    QtMaterialAppBarPrivate(QtMaterialAppBar *q);
    ~QtMaterialAppBarPrivate();

    void init();
    void updateChildrenColor();
    void setIconSize(const QSize &iconSize);

    void setNavIconType(Material::NavIconType type);

    QtMaterialAppBar *const q_ptr;

    QtMaterialAppBarLayout *layout;
    QtMaterialIconButton *navButton;
    QLabel *titleLabel;

    Material::NavIconType navIconType;
    QString title;
    QSize iconSize;

    bool useThemeColors;
    QColor foregroundColor;
    QColor backgroundColor;
};

#endif  // QTMATERIALAPPBAR_P_H
