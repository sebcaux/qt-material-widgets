#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "slider.h"

Handle::Handle(Slider *slider)
    : QWidget(slider),
      _slider(slider),
      _knobSize(12)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

Handle::~Handle()
{
}

void Handle::refreshGeometry()
{
    //QWidget *container = parentWidget();
    //Slider *container = _slider;
    const QSize s = sizeHint();

    setGeometry(QRect(_slider->orientation() == Qt::Horizontal
        ? QPoint(qBound(0, _position.x(), _slider->width()-s.width()), _slider->height()/2-s.height()/2)
        : QPoint(_slider->width()/2-s.width()/2, qBound(0, _position.y(), _slider->height()-s.height())), s));
//        ? QPoint(qBound(0, _position.x(), container->width()-s.width()), container->height()/2-s.height()/2)
//        : QPoint(container->width()/2-s.width()/2, qBound(0, _position.y(), container->height()-s.height())), s));

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
    brush.setColor(QColor(0, 0, 0));
    brush.setStyle(Qt::SolidPattern);

//    painter.drawRect(rect());

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    //painter.drawEllipse(0, 0, width(), height());
    painter.drawEllipse((width()-_knobSize)/2, (height()-_knobSize)/2, _knobSize, _knobSize);

    QWidget::paintEvent(event);
}

/*
void Handle::mousePressEvent(QMouseEvent *event)
{
    _offset = pos() - event->globalPos();

    _animation->setDirection(QAbstractAnimation::Forward);
    _animation->start();
}

void Handle::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    _animation->setDirection(QAbstractAnimation::Backward);
    _animation->start();
}
*/

//void Handle::enterEvent(QEvent *event)
//{
//    _slider->update();
//}
//
//void Handle::leaveEvent(QEvent *event)
//{
//    _slider->update();
//}

//void Handle::mouseMoveEvent(QMouseEvent *event)
//{
//    setRelativePosition(event->globalPos());
//    //_slider->update();
//    _slider->updateValue();
//}

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
      _animation(new QPropertyAnimation(this)),
      _drag(false),
      _hover(false),
      _handle(new Handle(this)),
      _orientation(Qt::Horizontal)
{
    _animation->setPropertyName("knobSize");
    _animation->setTargetObject(_handle);
    _animation->setStartValue(12);
    _animation->setEndValue(20);
    _animation->setDuration(100);

    setMouseTracking(true);
}

Slider::~Slider()
{
}

void Slider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect r = Qt::Vertical == _orientation
            ? QRect(width()/2-1, 0, 2, height())
            : QRect(0, height()/2-1, width(), 2);

    const QSize s = _handle->sizeHint();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(0, 0, 0, 40));

    if (Qt::Horizontal == _orientation) {
        r.adjust(s.width()/2, 0, -s.width()/2, 0);
    } else {
        r.adjust(0, s.height()/2, 0, -s.height()/2);
    }
    painter.fillRect(r, brush);

    painter.save();
    brush.setColor(QColor(0, 0, 0));

    const QPoint p = Qt::Vertical == _orientation
            ? QPoint(width(), _handle->y()+s.height()/2)
            : QPoint(_handle->x()+s.width()/2, height());
    painter.fillRect(r.intersected(QRect(QPoint(0, 0), p)), brush);
    painter.restore();

    if (_hover) {
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    QAbstractSlider::paintEvent(event);
}


void Slider::mousePressEvent(QMouseEvent *event)
{
    const QSize s = _handle->sizeHint();
    _handle->setOffset((event->pos() - QPoint(s.width(), s.height())/2) - event->globalPos());

    if (overHandle(event->pos())) {
        _drag = true;
        _animation->setDirection(QAbstractAnimation::Forward);
        _animation->start();
    } else if (overTrack(event->pos())) {
        _handle->setRelativePosition(event->globalPos());
        updateValue();
    }
    QAbstractSlider::mousePressEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (_drag) {
        _drag = false;
        _animation->setDirection(QAbstractAnimation::Backward);
        _animation->start();
    }
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    if (_drag) {
        _handle->setRelativePosition(event->globalPos());
        updateValue();
    } else {
        updateHoverState(event->pos());
    }
    QAbstractSlider::mouseMoveEvent(event);
}

void Slider::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    updateHoverState(mapFromGlobal(QCursor::pos()));
}

void Slider::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    if (_hover) {
        _hover = false;
        update();
    }
}

void Slider::resizeEvent(QResizeEvent *event)
{
    _handle->refreshGeometry();
    QAbstractSlider::resizeEvent(event);
}

bool Slider::overTrack(const QPoint &pos) const
{
    if (Qt::Horizontal == _orientation) {
        const int y = pos.y();
        const int h = height()/2;
        return (y >= h-2 && y <= h+2);
    } else {
        const int x = pos.x();
        const int w = width()/2;
        return (x >= w-2 && x <= w+2);
    }
}

bool Slider::overHandle(const QPoint &pos) const
{
    const int knob = _handle->knobSize();
    const int hl = _handle->x() + (20-knob)/2;
    const int ht = _handle->y() + (20-knob)/2;

    return (pos.x() >= hl && pos.x() <= hl+knob && pos.y() >= ht && pos.y() <= ht+knob);
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

void Slider::updateHoverState(const QPoint &pos)
{
    if (overTrack(pos) || (overHandle(pos))) {
        if (!_hover) {
            _hover = true;
            update();
        }
    } else {
        if (_hover) {
            _hover = false;
            update();
        }
    }
}
