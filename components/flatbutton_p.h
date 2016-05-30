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
    RippleOverlay        *ripple;
    FlatButtonDelegate   *delegate;
    Material::Role        role;
    Material::RippleStyle rippleStyle;
    qreal                 cornerRadius;
    Qt::BGMode            bgMode;
    QColor                primaryTextColor;
    QColor                secondaryTextColor;
    QColor                defaultTextColor;
    QColor                disabledTextColor;
    QColor                primaryBgColor;
    QColor                secondaryBgColor;
    QColor                defaultBgColor;
    qreal                 peakOpacity;
};

#endif // FLATBUTTON_P_H
