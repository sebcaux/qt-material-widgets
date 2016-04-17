#include <QWidget>
#include <QPainter>
#include "checkbox.h"

Checkbox::Checkbox(QWidget *parent)
    : QWidget(parent)
{
}

Checkbox::~Checkbox()
{
}

void Checkbox::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void Checkbox::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void Checkbox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(0, 0, 50, 50);

    QWidget::paintEvent(event);
}
