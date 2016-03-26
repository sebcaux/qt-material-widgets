#include <QAbstractButton>
#include <QDebug>
#include <QPainter>
#include "toggle.h"
#include "../lib/rippleoverlay.h"

Thumb::Thumb(QWidget *parent)
    : QWidget(parent)
{
}

Thumb::~Thumb()
{
}

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this))
{
}

Toggle::~Toggle()
{
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int h = height()/2;

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(QRect(0, h-h/2, width(), h+h/2), h, h);

}
