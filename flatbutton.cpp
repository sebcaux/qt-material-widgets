#include <QDebug>
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include "flatbutton.h"

FlatButton::FlatButton(QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this))
{
}

FlatButton::FlatButton(const QString &text, QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this))
{
    setText(text);
}

FlatButton::~FlatButton()
{
}

void FlatButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    updateOverlayGeometry();
}

void FlatButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter painter(this);

    QStyleOptionButton option;
    option.initFrom(this);
    option.features = QStyleOptionButton::None;
    option.features |= QStyleOptionButton::Flat;
    if (isChecked())
        option.state |= QStyle::State_On;
    option.text = text();
    option.icon = icon();
    option.iconSize = iconSize();

    painter.drawControl(QStyle::CE_PushButton, option);

    if (underMouse()) {
        QRect r = rect();
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter.setOpacity(0.1);
        painter.fillRect(r, brush);
    }
}

void FlatButton::mousePressEvent(QMouseEvent *event)
{
    _overlay->addRipple(event->pos());
}

void FlatButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    emit clicked();
}

void FlatButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    update();
}

void FlatButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    update();
}
