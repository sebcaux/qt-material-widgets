#include <QPainter>
#include "slider.h"

Handle::Handle(QWidget *parent)
    : QWidget(parent)
{
}

Handle::~Handle()
{
}

void Handle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    QWidget::paintEvent(event);
}

Slider::Slider(QWidget *parent)
    : QWidget(parent),
      _handle(new Handle(this))
{
    _handle->setGeometry(10, 10, 30, 30);
}

Slider::~Slider()
{
}

void Slider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    QWidget::paintEvent(event);
}
