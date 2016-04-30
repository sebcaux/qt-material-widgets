#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "slider.h"

Handle::Handle(Slider *slider)
    : QWidget(slider),
      _slider(slider),
      _animation(new QPropertyAnimation(this)),
      _scaleFactor(12)
{
    _animation->setPropertyName("scaleFactor");
    _animation->setTargetObject(this);
    _animation->setStartValue(12);
    _animation->setEndValue(20);
    _animation->setDuration(100);
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
    painter.setRenderHint(QPainter::Antialiasing);

//    QPen pen;
//    pen.setColor(Qt::black);
//    pen.setWidth(1);
//    painter.setPen(pen);
//    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    QBrush brush;
    brush.setColor(QColor(200, 200, 200));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    //painter.drawEllipse(0, 0, width(), height());
    //painter.drawRect(rect());
    painter.drawEllipse((width()-_scaleFactor)/2, (height()-_scaleFactor)/2, _scaleFactor, _scaleFactor);

    QWidget::paintEvent(event);
}

void Handle::mousePressEvent(QMouseEvent *event)
{
    _offset = pos() - event->globalPos();

    _animation->setDirection(QAbstractAnimation::Forward);
    _animation->start();
}

void Handle::mouseReleaseEvent(QMouseEvent *event)
{
    _animation->setDirection(QAbstractAnimation::Backward);
    _animation->start();
}

void Handle::mouseMoveEvent(QMouseEvent *event)
{
    setRelativePosition(event->globalPos());
    //_slider->update();
    _slider->updateValue();
}

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
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
            ? QRect(x-1, 0, 2, height())
            : QRect(0, y-1, width(), 2);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0));
    painter.fillRect(r, brush);

    painter.save();
    brush.setColor(QColor(255, 0, 0));
    const QPoint p = Qt::Vertical == _orientation
            ? QPoint(width(), _handle->y())
            : QPoint(_handle->x(), height());
    painter.fillRect(r.intersected(QRect(QPoint(0, 0), p)), brush);
    painter.restore();

    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    QAbstractSlider::paintEvent(event);
}


void Slider::mousePressEvent(QMouseEvent *event)
{
    if (Qt::Horizontal == _orientation
            ? isOnTrack(event->y(), height()/2)
            : isOnTrack(event->x(), width()/2))
    {
        const QSize s = _handle->sizeHint();
        _handle->setOffset((event->pos() - QPoint(s.width()/2, s.height()/2)) - event->globalPos());
        _handle->setRelativePosition(event->globalPos());
        _drag = true;
        //update();
        updateValue();
    } else {
        _drag = false;
    }
    QAbstractSlider::mousePressEvent(event);
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    if (_drag) {
        _handle->setRelativePosition(event->globalPos());
        //update();
        updateValue();
    }
    QAbstractSlider::mouseMoveEvent(event);
}

void Slider::resizeEvent(QResizeEvent *event)
{
    _handle->refreshGeometry();
    QAbstractSlider::resizeEvent(event);
}

void Slider::updateValue()
{
    const qreal tot = Qt::Horizontal == _orientation
            ? geometry().width()-_handle->width()
            : geometry().height()-_handle->height();

    const qreal r = Qt::Horizontal == _orientation
            ? _handle->geometry().left() / tot
            : _handle->geometry().top() / tot;

    // use QStyle::sliderValueFromPosition ??

    setValue((1-r)*minimum()+r*maximum());

    //setSliderPosition((1-r)*minimum()+r*maximum());
    //triggerAction(QAbstractSlider::SliderMove);

    update();
}
