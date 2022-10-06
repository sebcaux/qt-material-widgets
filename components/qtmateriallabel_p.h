#ifndef QTMATERIALLABEL_P_H
#define QTMATERIALLABEL_P_H

#include <QColor>
#include <QtGlobal>

#include "lib/qtmaterialtheme.h"

class QtMaterialLabel;

class QtMaterialLabelPrivate
{
    Q_DISABLE_COPY(QtMaterialLabelPrivate)
    Q_DECLARE_PUBLIC(QtMaterialLabel)

public:
    QtMaterialLabelPrivate(QtMaterialLabel *q);
    virtual ~QtMaterialLabelPrivate();

    void init();
    void updateColors();
    void updateFont();

    Material::FontType fontType;
    bool useThemeColors;
    QColor color;

    QtMaterialLabel *const q_ptr;
};

#endif  // QTMATERIALLABEL_P_H
