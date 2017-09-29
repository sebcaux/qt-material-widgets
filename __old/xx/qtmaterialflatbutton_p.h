#ifndef QTMATERIALFLATBUTTON_P_H
#define QTMATERIALFLATBUTTON_P_H

#include <QtGlobal>
#include <QColor>
#include "xxlib/qtmaterialtheme.h"

class QtMaterialFlatButton;
class QtMaterialRippleOverlay;
class QtMaterialFlatButtonStateMachine;

class QtMaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialFlatButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialFlatButton)

public:
    QtMaterialFlatButtonPrivate(QtMaterialFlatButton *q);
    virtual ~QtMaterialFlatButtonPrivate();

    void init();

    QtMaterialFlatButton             *const q_ptr;
    QtMaterialRippleOverlay          *rippleOverlay;
    QtMaterialFlatButtonStateMachine *stateMachine;
    XXMaterial::Role                    role;
    XXMaterial::RippleStyle             rippleStyle;
    XXMaterial::ButtonIconPlacement     iconPlacement;
    XXMaterial::OverlayStyle            overlayStyle;
    Qt::BGMode                        bgMode;
    QColor                            backgroundColor;
    QColor                            foregroundColor;
    QColor                            overlayColor;
    QColor                            disabledColor;
    QColor                            disabledBackgroundColor;
    qreal                             fixedRippleRadius;
    qreal                             cornerRadius;
    qreal                             baseOpacity;
    qreal                             fontSize;
    bool                              useThemeColors;
    bool                              useFixedRippleRadius;
    bool                              haloVisible;
};

#endif // QTMATERIALFLATBUTTON_P_H
