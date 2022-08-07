#ifndef QTMATERIALSLIDELAYOUT_P_H
#define QTMATERIALSLIDELAYOUT_P_H

#include <QEasingCurve>
#include <QtGlobal>

class QtMaterialSlideLayout;

class QPropertyAnimation;
class QParallelAnimationGroup;
class QWidget;

class QtMaterialSlideLayoutPrivate
{
    Q_DISABLE_COPY(QtMaterialSlideLayoutPrivate)
    Q_DECLARE_PUBLIC(QtMaterialSlideLayout)

public:
    QtMaterialSlideLayoutPrivate(QtMaterialSlideLayout *q);
    ~QtMaterialSlideLayoutPrivate();

    void init();

    QtMaterialSlideLayout *const q_ptr;

    QPropertyAnimation *prevWidgetAnimation;
    QPropertyAnimation *newWidgetAnimation;
    QParallelAnimationGroup *animationGroup;

    QWidget *prevWidget;
    QWidget *newWidget;
    int direction;

    uint animationDuration;
    QEasingCurve::Type animationType;
    Qt::Orientation orientation;
};

#endif  // QTMATERIALSLIDELAYOUT_P_H
