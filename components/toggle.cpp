#include <QAbstractButton>
#include <QDebug>
#include <QPainter>
#include "toggle.h"
#include "../lib/rippleoverlay.h"

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this))
{
    qDebug() << "1";
}

Toggle::~Toggle()
{
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    qDebug() << "2";

    QPainter painter(this);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawRect(rect());

    painter.drawRect(QRect(10, 10, 30, 30));
}
