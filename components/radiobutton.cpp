#include <QWidget>
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

    painter.drawRect(0, 50, 50, 50);

    QWidget::paintEvent(event);
}
