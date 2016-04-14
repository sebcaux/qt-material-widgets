#include <QWidget>
#include <QPainter>
#include "textfield.h"

TextField::TextField(QWidget *parent)
    : QWidget(parent)
{
}

TextField::~TextField()
{
}

void TextField::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void TextField::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void TextField::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(40, 0, 50, 50);

    QWidget::paintEvent(event);
}
