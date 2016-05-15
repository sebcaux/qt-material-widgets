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

FlatButton::FlatButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new FlatButtonPrivate(this))
{
}

FlatButton::FlatButton(const QString &text, QWidget *parent)
    : QPushButton(parent),
      d_ptr(new FlatButtonPrivate(this))
{
    setText(text);
}

FlatButton::~FlatButton()
{
}

void FlatButton::setRole(Material::Role role)
{
    Q_D(FlatButton);

    d->role = role;

    switch (role)
    {
    case Material::Primary:
        d->setTextColor("primary1");
        d->delegate->assignProperties();
        break;
    case Material::Secondary:
        d->setTextColor("accent1");
        d->delegate->assignProperties();
        break;
    default:
        d->setTextColor("text");
        d->delegate->assignProperties();
        break;
    }
    update();
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

    if (isEnabled() && bgOpacity > 0)
    {
        QPainter painter(this);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(d->delegate->backgroundColor());
        painter.setOpacity(bgOpacity);
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), 3, 3);
    }

    QStylePainter painter(this);

    QStyleOptionButton option;
    initStyleOption(&option);
    option.features |= QStyleOptionButton::Flat;

    painter.drawControl(QStyle::CE_PushButtonLabel, option);

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

    QColor color = palette().color(QPalette::Active, QPalette::ButtonText);

    Ripple *ripple = new Ripple(event->pos());
    ripple->setRadiusEndValue(100);
    ripple->setOpacityStartValue(0.4);
    ripple->setColor(color);

    d->ripple->addRipple(ripple);

    QPushButton::mousePressEvent(event);
}
