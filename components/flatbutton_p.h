#ifndef FLATBUTTON_P_H
#define FLATBUTTON_P_H

#include "flatbutton.h"
#include "lib/rippleoverlay.h"
#include "lib/theme.h"
#include "lib/style.h"
#include "flatbutton_internal.h"

class FlatButtonPrivate
{
    Q_DISABLE_COPY(FlatButtonPrivate)
    Q_DECLARE_PUBLIC(FlatButton)

public:
    FlatButtonPrivate(FlatButton *q)
        : q_ptr(q),
          role(Material::Default)
    {}

    void init();
    void setTextColor(const QString &themeColor);

    FlatButton *const q_ptr;
    RippleOverlay *ripple;
    FlatButtonDelegate *delegate;
    Material::Role role;
};

#endif // FLATBUTTON_P_H
