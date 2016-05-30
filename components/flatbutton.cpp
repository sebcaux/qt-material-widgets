#include "flatbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOption>
#include <QApplication>
#include <QDebug>
#include "lib/rippleoverlay.h"
#include "lib/ripple.h"
#include "flatbutton_p.h"

void FlatButtonPrivate::init()
{
    Q_Q(FlatButton);

    ripple = new RippleOverlay(q);
    delegate = new FlatButtonDelegate(q);

    Style &style = Style::instance();

    q->setStyle(&style);
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);

    QFont font(q->font());
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSizeF(10.5);
    font.setStyleName("Medium");
    q->setFont(font);

    QPalette palette;
    palette.setColor(QPalette::Disabled, QPalette::ButtonText,
                     style.themeColor("disabled"));
    q->setPalette(palette);
}

void FlatButtonPrivate::setPaletteColor(QPalette::ColorGroup group,
                                        QPalette::ColorRole role,
                                        const QString &themeColor)
{
    Q_Q(FlatButton);

    QPalette palette(q->palette());
    Style &style = Style::instance();

    palette.setColor(group, role, style.themeColor(themeColor));

    q->setPalette(palette);
}

FlatButton::FlatButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new FlatButtonPrivate(this))
{
    d_func()->init();
}

FlatButton::FlatButton(const QString &text, QWidget *parent)
    : QPushButton(parent),
      d_ptr(new FlatButtonPrivate(this))
{
    d_func()->init();

    setText(text);
}

FlatButton::~FlatButton()
{
}

void FlatButton::setRippleStyle(Material::RippleStyle style)
{
    Q_D(FlatButton);

    d->rippleStyle = style;
}

void FlatButton::setCornerRadius(qreal radius)
{
    Q_D(FlatButton);

    d->cornerRadius = radius;
    update();
}

qreal FlatButton::cornerRadius() const
{
    Q_D(const FlatButton);

    return d->cornerRadius;
}

void FlatButton::setRole(Material::Role role)
{
    Q_D(FlatButton);

    d->role = role;

    switch (role)
    {
    case Material::Primary:
        d->setPaletteColor(QPalette::Active, QPalette::ButtonText, "primary1");
        break;
    case Material::Secondary:
        d->setPaletteColor(QPalette::Active, QPalette::ButtonText, "accent1");
        break;
    default:
        d->setPaletteColor(QPalette::Active, QPalette::ButtonText, "text");
        break;
    }
    d->delegate->assignProperties();
    update();
}

FlatButton::FlatButton(FlatButtonPrivate &d, QWidget *parent)
    : QPushButton(parent),
      d_ptr(&d)
{
    d_func()->init();
}

void FlatButton::resizeEvent(QResizeEvent *event)
{
    Q_D(FlatButton);

    if (d->ripple) {
        d->ripple->setGeometry(rect());
    }

    QPushButton::resizeEvent(event);
}

void FlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(FlatButton);

    const qreal bgOpacity = d->delegate->backgroundOpacity();
    const qreal haloOpacity = d->delegate->focusHaloOpacity();
    const qreal hs = static_cast<qreal>(width())*d->delegate->focusHaloSize()/2;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (isEnabled() && bgOpacity > 0) {
        const qreal cr = d->cornerRadius;
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(d->delegate->backgroundColor());
        painter.setOpacity(bgOpacity);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), cr, cr);
    }

    if (isEnabled() && haloOpacity > 0) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(palette().color(QPalette::Active, QPalette::ButtonText));
        painter.setOpacity(haloOpacity);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        QPointF center = rect().center();
        painter.drawEllipse(center, hs, hs);
    }

    QStylePainter style(this);

    QStyleOptionButton option;
    initStyleOption(&option);
    option.features |= QStyleOptionButton::Flat;

    style.drawControl(QStyle::CE_PushButtonLabel, option);

#ifdef DEBUG_LAYOUT
    QPainter debug(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    debug.setPen(pen);
    debug.drawRect(rect());
#endif
}

void FlatButton::mousePressEvent(QMouseEvent *event)
{
    Q_D(FlatButton);

    if (Material::NoRipple == d->rippleStyle) {
        return;
    }

    QColor color = palette().color(QPalette::Active, QPalette::ButtonText);

    Ripple *ripple = new Ripple(Material::CenteredRipple == d->rippleStyle
        ? rect().center() : event->pos());

    ripple->setRadiusEndValue(100);
    ripple->setOpacityStartValue(0.4);
    ripple->setColor(color);

    d->ripple->addRipple(ripple);

    QPushButton::mousePressEvent(event);
}
