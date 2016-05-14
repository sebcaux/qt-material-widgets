#ifndef FLATBUTTON_P_H
#define FLATBUTTON_P_H

#include "flatbutton.h"
#include "lib/rippleoverlay.h"
#include "lib/theme.h"

class FlatButtonPrivate
{
    Q_DISABLE_COPY(FlatButtonPrivate)
    Q_DECLARE_PUBLIC(FlatButton)

public:
    FlatButtonPrivate(FlatButton *parent);

    FlatButton    *const q_ptr;
    RippleOverlay *const ripple;
    Material::Role role;
};

FlatButtonPrivate::FlatButtonPrivate(FlatButton *parent)
    : q_ptr(parent),
      ripple(new RippleOverlay(parent)),
      role(Material::Default)
{
    parent->setStyle(&Style::instance());
    parent->setAttribute(Qt::WA_Hover);
    parent->setMouseTracking(true);

    QFont font(parent->font());
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSizeF(10.5);
    font.setStyleName("Medium");
    parent->setFont(font);
}

#endif // FLATBUTTON_P_H
