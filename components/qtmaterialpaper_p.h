#ifndef QTMATERIALPAPER_P_H
#define QTMATERIALPAPER_P_H

#include <QColor>
#include <QtGlobal>

class QtMaterialPaper;

class QtMaterialPaperPrivate
{
    Q_DISABLE_COPY(QtMaterialPaperPrivate)
    Q_DECLARE_PUBLIC(QtMaterialPaper)

public:
    QtMaterialPaperPrivate(QtMaterialPaper *q);
    ~QtMaterialPaperPrivate();

    void init();

    QtMaterialPaper *const q_ptr;

    bool useThemeColors;
    QColor backgroundColor;
};

#endif  // QTMATERIALPAPER_P_H
