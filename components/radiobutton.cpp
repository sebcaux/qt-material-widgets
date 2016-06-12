#include <QPainter>
#include "radiobutton.h"

RadioButton::RadioButton(QWidget *parent)
    : QWidget(parent)
{
}

RadioButton::~RadioButton()
{
}

void RadioButton::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void RadioButton::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void RadioButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(rect());

    QWidget::paintEvent(event);
}
