#ifndef QTMATERIALFLATBUTTON_P_H
#define QTMATERIALFLATBUTTON_P_H

#include <QColor>
#include <QtGlobal>

#include "lib/qtmaterialtheme.h"

class QtMaterialFlatButton;
class QtMaterialRippleOverlay;
class QtMaterialFlatButtonStateMachine;

class QStateMachine;
class QState;
class QGraphicsDropShadowEffect;

class QtMaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialFlatButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialFlatButton)

public:
    QtMaterialFlatButtonPrivate(QtMaterialFlatButton *q);
    virtual ~QtMaterialFlatButtonPrivate();

    void init();
    void initRaiseEffect();
    void removeRaiseEffect();

    bool isTranparent() const;

    QtMaterialFlatButton *const q_ptr;
    QtMaterialRippleOverlay *rippleOverlay;
    QtMaterialFlatButtonStateMachine *stateMachine;

    QStateMachine *shadowStateMachine;
    QState *shadowNormalState;
    QState *shadowPressedState;
    QGraphicsDropShadowEffect *shadowEffect;

    Material::Role role;
    Material::ButtonType type;
    Material::RippleStyle rippleStyle;
    Material::ButtonIconPlacement iconPlacement;
    Material::OverlayStyle overlayStyle;
    Qt::Alignment textAlignment;
    QColor backgroundColor;
    QColor foregroundColor;
    QColor overlayColor;
    QColor disabledColor;
    QColor disabledBackgroundColor;
    qreal fixedRippleRadius;
    qreal cornerRadius;
    qreal baseOpacity;
    qreal fontSize;
    bool useThemeColors;
    bool useFixedRippleRadius;
    bool haloVisible;
};

#endif  // QTMATERIALFLATBUTTON_P_H
