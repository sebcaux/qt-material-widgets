#ifndef FLATBUTTON_P_H
#define FLATBUTTON_P_H

#include <QPalette>
#include "lib/rippleoverlay.h"
#include "lib/theme.h"
#include "lib/style.h"
#include "flatbutton_internal.h"

class FlatButton;

class FlatButtonPrivate
{
    Q_DISABLE_COPY(FlatButtonPrivate)
    Q_DECLARE_PUBLIC(FlatButton)

public:
    FlatButtonPrivate(FlatButton *q);
    virtual ~FlatButtonPrivate();

    void init();

    FlatButton           *const q_ptr;
    RippleOverlay        *const ripple;
    FlatButtonDelegate         *delegate;
    Material::Role              role;
    Material::RippleStyle       rippleStyle;
    Material::IconPlacement     iconPlacement;
    qreal                       cornerRadius;
    Qt::BGMode                  bgMode;
    QColor                      textColor;
    QColor                      backgroundColor;
    QColor                      disabledTextColor;
    bool                        useThemeColors;
    bool                        showHalo;
    qreal                       peakOpacity;
    bool                        useFixedRippleRadius;
    qreal                       fixedRippleRadius;
};

#endif // FLATBUTTON_P_H
