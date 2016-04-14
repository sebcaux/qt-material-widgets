#include <QWidget>
#include <QPainter>
#include "avatar.h"

Avatar::Avatar(QWidget *parent)
    : QWidget(parent)
{
}

Avatar::~Avatar()
{
}

void Avatar::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void Avatar::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void Avatar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(0, 50, 50, 50);

    QWidget::paintEvent(event);
}
