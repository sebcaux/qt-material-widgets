#ifndef QTMATERIALWIDGET_P_H
#define QTMATERIALWIDGET_P_H

#include <QColor>
#include <QtGlobal>

class QtMaterialWidget;

class QtMaterialWidgetPrivate
{
    Q_DISABLE_COPY(QtMaterialWidgetPrivate)
    Q_DECLARE_PUBLIC(QtMaterialWidget)

public:
    QtMaterialWidgetPrivate(QtMaterialWidget *q);
    ~QtMaterialWidgetPrivate();

    void init();

    QtMaterialWidget *const q_ptr;

    bool useThemeColors;
    QColor backgroundColor;
};

#endif  // QTMATERIALWIDGET_P_H
