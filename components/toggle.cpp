#include "toggle.h"
#include <QPainter>
#include "toggle_p.h"

TogglePrivate::TogglePrivate(Toggle *q)
    : q_ptr(q),
      orientation(Qt::Horizontal)
{
}

void TogglePrivate::init()
{
    Q_Q(Toggle);

    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      d_ptr(new TogglePrivate(this))
{
    d_func()->init();
}

Toggle::~Toggle()
{
}

QSize Toggle::sizeHint() const
{
    Q_D(const Toggle);

    return Qt::Horizontal == d->orientation
        ? QSize(64, 48)
        : QSize(48, 64);
}

void Toggle::setOrientation(Qt::Orientation orientation)
{
    Q_D(Toggle);

    if (d->orientation == orientation)
        return;
    d->orientation = orientation;
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(Toggle);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == d->orientation) {
        const int h = height()/2;
        const QRect r(0, h/2, width(), h);
        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
    } else {
        const int w = width()/2;
        const QRect r(w/2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w/2-4, w/2-4);
    }
}

//#include <QAbstractButton>
//#include <QPropertyAnimation>
//#include <QMouseEvent>
//#include <QEvent>
//#include <QMouseEvent>
//#include <QPainter>
//#include "toggle.h"
//#include "../lib/rippleoverlay.h"
//#include "../lib/customshadoweffect.h"
//
//Thumb::Thumb(Toggle *parent)
//    : QWidget(parent),
//      _toggle(parent),
//      _animation(new QPropertyAnimation(this)),
//      _progress(1),
//      _offset(0)
//{
//    parent->installEventFilter(this);
//
//    _animation->setPropertyName("progress");
//    _animation->setTargetObject(this);
//    _animation->setDuration(350);
//    _animation->setStartValue(1);
//    _animation->setEndValue(0);
//}
//
//Thumb::~Thumb()
//{
//}
//
//void Thumb::setProgress(qreal progress)
//{
//    if (_progress == progress)
//        return;
//
//    _progress = progress;
//
//    const QSize s(Qt::Horizontal == _toggle->orientation()
//            ? size() : size().transposed());
//    setOffset(progress*static_cast<qreal>(s.width()-s.height()));
//
//    _toggle->updateOverlayGeometry();
//    update();
//}
//
//bool Thumb::eventFilter(QObject *obj, QEvent *event)
//{
//    const QEvent::Type type = event->type();
//    if (QEvent::Resize == type || QEvent::Move == type) {
//        setGeometry(parentWidget()->rect().adjusted(8, 8, -8, -8));
//    } else if (QEvent::MouseButtonRelease == type) {
//        return true;
//    }
//    return QWidget::eventFilter(obj, event);
//}
//
//void Thumb::mouseReleaseEvent(QMouseEvent *event)
//{
//    const bool checked = _toggle->isChecked();
//
//    _toggle->setChecked(!checked);
//
//    if (QAbstractAnimation::Running != _animation->state()) {
//        _animation->setEasingCurve(checked
//            ? QEasingCurve::OutCubic
//            : QEasingCurve::InCubic);
//    }
//
//    _animation->setDirection(checked
//        ? QAbstractAnimation::Forward
//        : QAbstractAnimation::Backward);
//    _animation->start();
//
//    emit clicked();
//
//    QWidget::mouseReleaseEvent(event);
//}
//
//void Thumb::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::white);
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//
//    if (Qt::Horizontal == _toggle->orientation()) {
//        const int s = height()-10;
//        painter.drawEllipse(5+_offset, 5, s, s);
//    } else {
//        const int s = width()-10;
//        painter.drawEllipse(5, 5+_offset, s, s);
//    }
//}
//
//void Toggle::updateOverlayGeometry()
//{
//    const int offset = _thumb->offset();
//    if (Qt::Horizontal == _orientation) {
//        _overlay->setGeometry(geometry().adjusted(-10+offset, -20, 10+offset, 20));
//    } else {
//        _overlay->setGeometry(geometry().adjusted(-10, -20+offset, 10, 20+offset));
//    }
//}
//
//Toggle::Toggle(QWidget *parent)
//    : QAbstractButton(parent),
//      _thumb(new Thumb(this)),
//      _overlay(new RippleOverlay(parent)),
//      _orientation(Qt::Horizontal)
//{
//    setCheckable(true);
//    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
//
//    CustomShadowEffect *effect = new CustomShadowEffect;
//    effect->setDistance(0);
//    effect->setBlurRadius(6);
//    effect->setColor(QColor(0, 0, 0, 100));
//
//    _thumb->setGraphicsEffect(effect);
//    _thumb->installEventFilter(this);
//
//    connect(_thumb, SIGNAL(clicked()), this, SLOT(addRipple()));
//}
//
//Toggle::~Toggle()
//{
//}
//
//QSize Toggle::sizeHint() const
//{
//    return Qt::Horizontal == _orientation
//        ? QSize(64, 48)
//        : QSize(48, 64);
//}
//
//void Toggle::setOrientation(Qt::Orientation orientation)
//{
//    if (_orientation == orientation)
//        return;
//    _orientation = orientation;
//}
//
//void Toggle::addRipple()
//{
//    if (Qt::Horizontal == _orientation) {
//        const int d = height()/2;
//        const int w = _thumb->height()/2+10;
//        _overlay->addRipple(QPoint(10+d, 20+d), w);
//    } else {
//        const int d = width()/2;
//        const int w = _thumb->width()/2+10;
//        _overlay->addRipple(QPoint(10+d, 20+d), w);
//    }
//}
//
//bool Toggle::event(QEvent *event)
//{
//    const QEvent::Type type = event->type();
//    if (QEvent::ParentChange == type && parentWidget()) {
//        _overlay->setParent(parentWidget());
//    } else if (QEvent::Resize == type || QEvent::Move == type) {
//        _overlay->setGeometry(geometry().adjusted(-10, -20, 10, 20));
//    }
//    return QAbstractButton::event(event);
//}
//
//void Toggle::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//
//    QBrush brush;
//    brush.setColor(QColor(180, 180, 180));
//    brush.setStyle(Qt::SolidPattern);
//    painter.setBrush(brush);
//
//    painter.setPen(Qt::NoPen);
//
//    if (Qt::Horizontal == _orientation) {
//        const int h = height()/2;
//        const QRect r(0, h/2, width(), h);
//        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
//    } else {
//        const int w = width()/2;
//        const QRect r(w/2, 0, w, height());
//        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w/2-4, w/2-4);
//    }
//}
//
