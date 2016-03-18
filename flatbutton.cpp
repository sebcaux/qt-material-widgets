#include <QDebug>
#include <QStylePainter>
#include <QStyleOptionButton>
#include "flatbutton.h"

FlatButton::FlatButton(QWidget *parent)
    : QAbstractButton(parent)
{
}

FlatButton::FlatButton(const QString &text, QWidget *parent)
    : QAbstractButton(parent)
{
    setText(text);
}

FlatButton::~FlatButton()
{
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
