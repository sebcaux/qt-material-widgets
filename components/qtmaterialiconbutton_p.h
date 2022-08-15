#ifndef QTMATERIALICONBUTTON_P_H
#define QTMATERIALICONBUTTON_P_H

#include <QColor>
#include <QtGlobal>

class QtMaterialIconButton;
class QtMaterialRippleOverlay;

class QtMaterialIconButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialIconButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialIconButton)

public:
    QtMaterialIconButtonPrivate(QtMaterialIconButton *q);
    virtual ~QtMaterialIconButtonPrivate();

    void init();
    void updateRipple();

    bool useThemeColors;
    QColor color;
    QColor disabledColor;

    QtMaterialRippleOverlay *rippleOverlay;

    QtMaterialIconButton *const q_ptr;
};

#endif  // QTMATERIALICONBUTTON_P_H
