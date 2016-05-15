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
    FlatButtonPrivate(FlatButton *parent);

    QColor textColor() const;
    void setTextColor(const QString &themeColor);

    FlatButton         *const q_ptr;
    RippleOverlay      *const ripple;
    FlatButtonDelegate *const delegate;
    Material::Role role;
};

FlatButtonPrivate::FlatButtonPrivate(FlatButton *parent)
    : q_ptr(parent),
      ripple(new RippleOverlay(parent)),
      delegate(new FlatButtonDelegate(parent)),
      role(Material::Default)
{
    Style &style = Style::instance();

    parent->setStyle(&style);
    parent->setAttribute(Qt::WA_Hover);
    parent->setMouseTracking(true);

    QFont font(parent->font());
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSizeF(10.5);
    font.setStyleName("Medium");
    parent->setFont(font);

    QPalette palette;
    palette.setColor(QPalette::Disabled, QPalette::ButtonText,
                     style.themeColor("disabled"));
    parent->setPalette(palette);
}

QColor FlatButtonPrivate::textColor() const
{
    Q_Q(const FlatButton);

    return q->palette().color(QPalette::Active, QPalette::ButtonText);
}

void FlatButtonPrivate::setTextColor(const QString &themeColor)
{
    Q_Q(FlatButton);

    QPalette palette(q->palette());
    Style &style = Style::instance();

    palette.setColor(QPalette::Active, QPalette::ButtonText,
                     style.themeColor(themeColor));

    q->setPalette(palette);
}

#endif // FLATBUTTON_P_H
