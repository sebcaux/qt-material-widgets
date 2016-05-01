#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "slider.h"

Handle::Handle(Slider *slider)
    : QWidget(slider),
      _slider(slider),
      _knobSize(12),
      _haloSize(0)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

Handle::~Handle()
{
}

void Handle::refreshGeometry()
{
    const QSize handle = sizeHint();
    setGeometry(QRect(_slider->orientation() == Qt::Horizontal
        ? QPoint(qBound(0, _position.x(), _slider->width()-handle.width()), _slider->height()/2-handle.height()/2)
        : QPoint(_slider->width()/2-handle.width()/2, qBound(0, _position.y(), _slider->height()-handle.height())), handle));
    update();
}

void Handle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //painter.drawRect(rect());

    QBrush brush;
    brush.setColor(QColor(0, 0, 0));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawEllipse(QRectF((width()-_knobSize)/2, (height()-_knobSize)/2, _knobSize, _knobSize));

    painter.setOpacity(0.2);
    painter.drawEllipse(QRectF((width()-_haloSize)/2, (height()-_haloSize)/2, _haloSize, _haloSize));

    QWidget::paintEvent(event);
}

Slider::Slider(QWidget *parent)
    : QAbstractSlider(parent),
      _knobAnimation(new QPropertyAnimation(this)),
      _haloAnimation(new QPropertyAnimation(this)),
      _handle(new Handle(this)),
      _drag(false),
      _hover(false),
      _orientation(Qt::Horizontal)
{
    _knobAnimation->setPropertyName("knobSize");
    _knobAnimation->setTargetObject(_handle);
    _knobAnimation->setStartValue(12);
    _knobAnimation->setEndValue(20);
    _knobAnimation->setDuration(100);

    _haloAnimation->setPropertyName("haloSize");
    _haloAnimation->setTargetObject(_handle);
    _haloAnimation->setStartValue(12);
    _haloAnimation->setEndValue(30);
    _haloAnimation->setDuration(220);

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

    const QSize handle = _handle->sizeHint();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(_hover ? QColor(0, 0, 0, 80) : QColor(0, 0, 0, 40));

    if (Qt::Horizontal == _orientation) {
        r.adjust(handle.width()/2, 0, -handle.width()/2, 0);
    } else {
        r.adjust(0, handle.height()/2, 0, -handle.height()/2);
    }
    painter.fillRect(r, brush);

    painter.save();
    brush.setColor(QColor(0, 0, 0));
    const QPoint range = Qt::Vertical == _orientation
            ? QPoint(width(), _handle->y()+handle.height()/2)
            : QPoint(_handle->x()+handle.width()/2, height());
    painter.fillRect(r.intersected(QRect(QPoint(0, 0), range)), brush);
    painter.restore();

    QAbstractSlider::paintEvent(event);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    const QPoint pos = event->pos();
    const bool oh = overHandle(pos);

    if (oh || overTrack(pos)) {
        const QSize handle = _handle->sizeHint();
        _handle->setOffset((pos - QPoint(handle.width(), handle.height())/2) - event->globalPos());
        _handle->setRelativePosition(event->globalPos());
        _drag = true;
        _knobAnimation->setDirection(QAbstractAnimation::Forward);
        _knobAnimation->start();

        if (oh) {
            _haloAnimation->setDirection(QAbstractAnimation::Backward);
            _haloAnimation->start();
        } else {
            _haloAnimation->stop();
            _handle->setHaloSize(0);
        }
        updateValue();
    }
    QAbstractSlider::mousePressEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    if (_drag) {
        _drag = false;
        _hover = false;
        _knobAnimation->setDirection(QAbstractAnimation::Backward);
        _knobAnimation->start();
        updateHoverState(mapFromGlobal(QCursor::pos()));
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

    endHover();
}

void Slider::resizeEvent(QResizeEvent *event)
{
    _handle->refreshGeometry();
    QAbstractSlider::resizeEvent(event);
}

bool Slider::overTrack(const QPoint &pos) const
{
    if (Qt::Horizontal == _orientation) {
        const int handleW = _handle->width();
        return QRect(handleW/2, height()/2-4, width()-handleW, 8).contains(pos);
    } else {
        const int handleH = _handle->height();
        return QRect(width()/2-4, handleH/2, 8, height()-handleH).contains(pos);
    }
}

bool Slider::overHandle(const QPoint &pos) const
{
    const int knob = _handle->knobSize();
    const int hl = _handle->x() + (20-knob)/2;    // @TODO: 20 should not be hard coded
    const int ht = _handle->y() + (20-knob)/2;    // @TODO: 20 should not be hard coded

    return (pos.x() > hl - 10 && pos.x() < hl+knob + 10
         && pos.y() > ht - 10 && pos.y() < ht+knob + 10);
}

void Slider::updateValue()
{
    const qreal tot = Qt::Horizontal == _orientation
            ? geometry().width()-_handle->width()
            : geometry().height()-_handle->height();

    const qreal r = Qt::Horizontal == _orientation
            ? _handle->geometry().left() / tot
            : _handle->geometry().top() / tot;

    // @TODO: use QStyle::sliderValueFromPosition()

    setValue((1-r)*minimum()+r*maximum());

    update();
}

void Slider::updateHoverState(const QPoint &pos)
{
    if (overTrack(pos) || (overHandle(pos))) {
        beginHover();
    } else {
        endHover();
    }
}

void Slider::beginHover() {
    if (!_hover) {
        _hover = true;
        _haloAnimation->setDirection(QAbstractAnimation::Forward);
        _haloAnimation->start();
        update();
    }
}

void Slider::endHover()
{
    if (_hover) {
        _hover = false;
        if (_handle->haloSize() > 12) {
            _haloAnimation->setDirection(QAbstractAnimation::Backward);
            _haloAnimation->start();
        }
        update();
    }
}
