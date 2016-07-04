#include "flatbutton.h"
#include "flatbutton_p.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOption>
#include <QApplication>
#include <QDebug>
#include "lib/rippleoverlay.h"
#include "lib/ripple.h"

FlatButtonPrivate::FlatButtonPrivate(FlatButton *q)
    : q_ptr(q),
      ripple(new RippleOverlay), //new RippleOverlay(q)),
      delegate(0), //new FlatButtonDelegate(q)),
      role(Material::Default),
      rippleStyle(Material::PositionedRipple),
      iconPlacement(Material::LeftIcon),
      cornerRadius(3),
      bgMode(Qt::TransparentMode),
      useThemeColors(true),
      showHalo(true),
      peakOpacity(0.08),
      useFixedRippleRadius(false),
      fixedRippleRadius(64)
{
    qDebug() << "FlatButtonPrivate";
}

FlatButtonPrivate::~FlatButtonPrivate()
{
}

void FlatButtonPrivate::init()
{
    Q_Q(FlatButton);

    ripple->setParent(q);
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

QSize FlatButton::sizeHint() const
{
    ensurePolished();

    QSize size = fontMetrics().size(Qt::TextSingleLine, text());

    int h = qMax(size.height(), iconSize().height());
    int w = size.width();

    if (!icon().isNull()) {
        w += iconSize().width()+12;
    }

    return QSize(20+w, 20+h);
}

void FlatButton::setHasFixedRippleRadius(bool value)
{
    Q_D(FlatButton);

    d->useFixedRippleRadius = value;
}

bool FlatButton::hasFixedRippleRadius() const
{
    Q_D(const FlatButton);

    return d->useFixedRippleRadius;
}

void FlatButton::setFixedRippleRadius(qreal radius)
{
    Q_D(FlatButton);

    d->fixedRippleRadius = radius;
    setHasFixedRippleRadius(true);
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

void FlatButton::setIconPlacement(Material::IconPlacement placement)
{
    Q_D(FlatButton);

    d->iconPlacement = placement;
    update();
}

Material::IconPlacement FlatButton::iconPlacement() const
{
    Q_D(const FlatButton);

    return d->iconPlacement;
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

void FlatButton::setShowHalo(bool state)
{
    Q_D(FlatButton);

    d->showHalo = state;
    update();
}

bool FlatButton::showHalo() const
{
    Q_D(const FlatButton);

    return d->showHalo;
}

FlatButton::FlatButton(FlatButtonPrivate &d, QWidget *parent)
    : QPushButton(parent),
      d_ptr(&d)
{
    d_func()->init();

    qDebug() << "FlatButton::FlatButton";
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
    const qreal cr = d->cornerRadius;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (Qt::OpaqueMode == d->bgMode) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundColor());
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

    paintHalo(&painter);

    //

    painter.setPen(textColor());
    painter.setOpacity(1);

    if (icon().isNull())
    {
        painter.drawText(rect(), Qt::AlignCenter, text());
    }
    else
    {
        QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));

        QSize base(size()-textSize);

        const int pad = 12;
        const int iw = iconSize().width() + pad;

        QPoint pos((base.width()-iw)/2, 0);

        QRect textGeometry(pos + QPoint(0, base.height()/2), textSize);
        QRect iconGeometry(pos + QPoint(0, (height()-iconSize().height())/2), iconSize());

        if (Material::LeftIcon == d->iconPlacement) {
            textGeometry.translate(iw, 0);
        } else {
            iconGeometry.translate(textSize.width() + pad, 0);
        }

        painter.drawText(textGeometry, Qt::AlignCenter, text());
        icon().paint(&painter, iconGeometry);
    }

    /*
    QStylePainter style(this);

    QStyleOptionButton option;
    initStyleOption(&option);
    option.features |= QStyleOptionButton::Flat;

    style.setOpacity(1);
    style.drawControl(QStyle::CE_PushButtonLabel, option);
    */

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
        return QPushButton::mousePressEvent(event);
    }

    Ripple *ripple = new Ripple(Material::CenteredRipple == d->rippleStyle
        ? rect().center()
        : event->pos());

    ripple->setRadiusEndValue(width()/2);
    ripple->setOpacityStartValue(0.35);
    ripple->setColor(palette().color(QPalette::Active, QPalette::ButtonText));
    ripple->setDuration(600, 1300);

    if (d->useFixedRippleRadius) {
        ripple->setRadiusEndValue(d->fixedRippleRadius);
    }

    d->ripple->addRipple(ripple);

    QPushButton::mousePressEvent(event);
}

void FlatButton::paintHalo(QPainter *painter)
{
    Q_D(FlatButton);

    if (!d->showHalo)
        return;

    const qreal haloOpacity = d->delegate->haloOpacity();
    const qreal s = d->delegate->haloScaleFactor()*d->delegate->haloSize()*0.7;
    const qreal hs = static_cast<qreal>(width())*s;

    if (isEnabled() && haloOpacity > 0) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(palette().color(QPalette::Active, QPalette::ButtonText));
        painter->setOpacity(haloOpacity);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        QPointF center = rect().center();
        painter->drawEllipse(center, hs, hs);
    }
}
