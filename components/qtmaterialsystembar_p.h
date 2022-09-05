#ifndef QTMATERIALSYSTEMBAR_P_H
#define QTMATERIALSYSTEMBAR_P_H

#include <QtGlobal>

#include <QColor>

class QBasicTimer;
class QtMaterialSystemBar;

class QtMaterialSystemBarPrivate
{
    Q_DISABLE_COPY(QtMaterialSystemBarPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSystemBar)

public:
    QtMaterialSystemBarPrivate(QtMaterialSystemBar *q);
    ~QtMaterialSystemBarPrivate();

    void init();

    QtMaterialSystemBar *const q_ptr;

    QBasicTimer *timer;

    QString dateTimeFormat;
    bool useThemeColors;
    QColor backgroundColor;
    QColor textColor;
};

#endif  // QTMATERIALSYSTEMBAR_P_H
