#ifndef QTMATERIALCANVAS_P_H
#define QTMATERIALCANVAS_P_H

#include <QColor>
#include <QtGlobal>

class QtMaterialCanvas;

class QtMaterialCanvasPrivate
{
    Q_DISABLE_COPY(QtMaterialCanvasPrivate)
    Q_DECLARE_PUBLIC(QtMaterialCanvas)

public:
    QtMaterialCanvasPrivate(QtMaterialCanvas *q);
    ~QtMaterialCanvasPrivate();

    void init();
    void updateOrientation();

    QtMaterialCanvas *const q_ptr;

    Qt::Orientation orientation;
    bool useThemeColors;
    QColor backgroundColor;
};

#endif  // QTMATERIALCANVAS_P_H
