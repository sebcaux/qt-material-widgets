#include "flatbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOption>
#include <QApplication>
#include "lib/rippleoverlay.h"
#include "lib/ripple.h"
#include "flatbutton_p.h"

FlatButtonPrivate::FlatButtonPrivate(FlatButton *q)
    : q_ptr(q),
      role(Material::Default),
      rippleStyle(Material::PositionedRipple),
      cornerRadius(3),
      bgMode(Qt::TransparentMode),
      useThemeColors(true),
      peakOpacity(0.15)
{
}

FlatButtonPrivate::~FlatButtonPrivate()
{
}

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

    delegate->updatePalette();
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

Material::RippleStyle FlatButton::rippleStyle() const
{
    Q_D(const FlatButton);

    return d->rippleStyle;
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

void FlatButton::setBackgroundMode(Qt::BGMode mode)
{
    Q_D(FlatButton);

    d->bgMode = mode;
    update();
}

Qt::BGMode FlatButton::backgroundMode() const
{
    Q_D(const FlatButton);

    return d->bgMode;
}

void FlatButton::setTextColor(const QColor &color)
{
    Q_D(FlatButton);

    d->textColor = color;
    setUseThemeColors(false);
}

QColor FlatButton::textColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->textColor.isValid()) {
        Style &style = Style::instance();
        if (Qt::OpaqueMode == d->bgMode) {
            return style.themeColor("canvas");
        }
        switch (d->role)
        {
        case Material::Primary:
            return style.themeColor("primary1");
        case Material::Secondary:
            return style.themeColor("accent1");
        case Material::Default:
        default:
            return style.themeColor("text");
        }
    } else {
        return d->textColor;
    }
}

void FlatButton::setBackgroundColor(const QColor &color)
{
    Q_D(FlatButton);

    d->backgroundColor = color;
    setUseThemeColors(false);
}

QColor FlatButton::backgroundColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        Style &style = Style::instance();
        switch (d->role)
        {
        case Material::Primary:
            return style.themeColor("primary1");
        case Material::Secondary:
            return style.themeColor("accent1");
        case Material::Default:
        default:
            return style.themeColor("text");
        }
    } else {
        return d->backgroundColor;
    }
}

void FlatButton::setDisabledTextColor(const QColor &color)
{
    Q_D(FlatButton);

    d->disabledTextColor = color;
    setUseThemeColors(false);
}

QColor FlatButton::disabledTextColor() const
{
    Q_D(const FlatButton);

    if (d->useThemeColors || !d->disabledTextColor.isValid()) {
        return Style::instance().themeColor("disabled");
    } else {
        return d->disabledTextColor;
    }
}

void FlatButton::setPeakOpacity(qreal opacity)
{
    Q_D(FlatButton);

    d->peakOpacity = opacity;
    d->delegate->updatePalette();
}

qreal FlatButton::peakOpacity() const
{
    Q_D(const FlatButton);

    return d->peakOpacity;
}

void FlatButton::setRole(Material::Role role)
{
    Q_D(FlatButton);

    d->role = role;
    d->delegate->updatePalette();
}

Material::Role FlatButton::role() const
{
    Q_D(const FlatButton);

    return d->role;
}

void FlatButton::setUseThemeColors(bool value)
{
    Q_D(FlatButton);

    d->useThemeColors = value;
    d->delegate->updatePalette();
}

bool FlatButton::useThemeColors() const
{
    Q_D(const FlatButton);

    return d->useThemeColors;
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
    const qreal haloOpacity = d->delegate->haloOpacity();
    const qreal s = d->delegate->haloScaleFactor()*d->delegate->haloSize()*0.7;
    const qreal hs = static_cast<qreal>(width())*s;
    const qreal cr = d->cornerRadius;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (Qt::OpaqueMode == d->bgMode) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);

        QColor brushColor;
        if (d->useThemeColors || !d->backgroundColor.isValid()) {
            Style &style = Style::instance();
            switch (d->role)
            {
            case Material::Primary:
                brushColor = style.themeColor("primary1");
                break;
            case Material::Secondary:
                brushColor = style.themeColor("accent1");
                break;
            case Material::Default:
            default:
                brushColor = style.themeColor("text");
                break;
            }
        } else {
             brushColor = d->backgroundColor;
        }

        brush.setColor(brushColor);
        painter.setOpacity(1);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), cr, cr);
    }

    if (isEnabled() && bgOpacity > 0) {
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

    Ripple *ripple = new Ripple(Material::CenteredRipple == d->rippleStyle
        ? rect().center()
        : event->pos());

    ripple->setRadiusEndValue(width()*0.45);
    ripple->setOpacityStartValue(0.4);
    ripple->setColor(palette().color(QPalette::Active, QPalette::ButtonText));
    ripple->setDuration(500);

    d->ripple->addRipple(ripple);

    QPushButton::mousePressEvent(event);
}
