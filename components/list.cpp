#include "list.h"
#include <QWidget>
#include <QPainter>

List::List(QWidget *parent)
    : QWidget(parent)
{
}

List::~List()
{
}

void List::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void List::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void List::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(50, 250, 50, 50);

    QWidget::paintEvent(event);
}
