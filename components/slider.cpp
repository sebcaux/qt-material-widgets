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

void Handle::refreshGeometry()
{
    QWidget *container = parentWidget();
    const QSize s = sizeHint();

    setGeometry(QRect(_slider->orientation() == Qt::Horizontal
        ? QPoint(qBound(0, _position.x(), container->width()-s.width()), container->height()/2-s.height()/2)
        : QPoint(container->width()/2-s.width()/2, qBound(0, _position.y(), container->height()-s.height())), s));

    update();
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
    _offset = pos() - event->globalPos();
}

void Handle::mouseMoveEvent(QMouseEvent *event)
{
    setRelativePosition(event->globalPos());
}

Slider::Slider(QWidget *parent)
    : QWidget(parent),
      _drag(false),
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
    const QPoint p = event->pos();

    if (Qt::Horizontal == _orientation
            ? touchesRail(p.y(), height()/2)
            : touchesRail(p.x(), width()/2))
    {
        const QPoint newPos = p - QPoint(s.width()/2, s.height()/2);
        _handle->setPosition(newPos);
        _handle->setOffset(newPos - event->globalPos());
        _drag = true;
    } else {
        _drag = false;
    }
    QWidget::mousePressEvent(event);
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    if (_drag) {
        _handle->setRelativePosition(event->globalPos());
    }
    QWidget::mouseMoveEvent(event);
}

void Slider::resizeEvent(QResizeEvent *event)
{
    _handle->refreshGeometry();
    QWidget::resizeEvent(event);
}


bool Slider::touchesRail(int p, int x) const
{
    return (p >= x-2 && p < x+2);
}
