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

    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);

    QRect r = rect();
    painter.drawEllipse(r.center(), 20, 20);

    QWidget::paintEvent(event);
}
