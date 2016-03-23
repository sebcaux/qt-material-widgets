#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include "slider.h"

Handle::Handle(Slider *slider)
    : QWidget(slider),
      _slider(slider)
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

void Handle::mousePressEvent(QMouseEvent *event)
{
    _eventPos = event->globalPos();
    _offset = pos();
}

void Handle::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void Handle::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    QWidget *container = parentWidget();
    const QPoint d = _offset + event->globalPos() - _eventPos;
    const QSize  s = sizeHint();
    QRect r(_slider->orientation() == Qt::Horizontal
        ? QPoint(qBound(0, d.x(), container->width()-s.width()), container->height()/2-s.height()/2)
        : QPoint(container->width()/2-s.width()/2, qBound(0, d.y(), container->height()-s.height())), s);
    setGeometry(r);
}

Slider::Slider(QWidget *parent)
    : QWidget(parent),
      _handle(new Handle(this)),
      _orientation(Qt::Horizontal)
{
}

Slider::~Slider()
{
}

void Slider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    const int x = width()/2;
    const int y = height()/2;

    QRect r = Qt::Vertical == _orientation
            ? QRect(x-2, 0, 4, height())
            : QRect(0, y-2, width(), 4);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0));
    painter.fillRect(r, brush);

    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    QWidget::paintEvent(event);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    const QSize s = _handle->sizeHint();

    _handle->setGeometry(QRect(Qt::Horizontal == _orientation
        ? QPoint(event->pos().x()-s.width()/2, height()/2-s.height()/2)
        : QPoint(width()/2-s.width()/2, event->pos().y()-s.height()/2), s));

    QWidget::mousePressEvent(event);
}
