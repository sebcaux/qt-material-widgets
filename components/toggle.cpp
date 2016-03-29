#include <QAbstractButton>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include "toggle.h"
#include "../lib/rippleoverlay.h"
#include "../lib/customshadoweffect.h"

Thumb::Thumb(Toggle *parent)
    : QWidget(parent),
      _toggle(parent),
      _animation(new QPropertyAnimation(this)),
      _progress(1),
      _offset(0)
{
    parent->installEventFilter(this);

    _animation->setPropertyName("progress");
    _animation->setTargetObject(this);
    _animation->setDuration(350);
    _animation->setStartValue(1);
    _animation->setEndValue(0);
}

Thumb::~Thumb()
{
}

void Thumb::setProgress(qreal progress)
{
    if (_progress == progress)
        return;
    _progress = progress;

    const QSize s(Qt::Horizontal == _toggle->orientation()
            ? size() : size().transposed());
    setOffset(progress*static_cast<qreal>(s.width()-s.height()));

    emit progressChanged(progress);
    update();
}

bool Thumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect().adjusted(8, 8, -8, -8));
    }
    return QWidget::eventFilter(obj, event);
}

void Thumb::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    const bool checked = _toggle->isChecked();
    _animation->setDirection(checked
        ? QAbstractAnimation::Forward
        : QAbstractAnimation::Backward);
    if (QAbstractAnimation::Running != _animation->state()) {
        _animation->setEasingCurve(checked
            ? QEasingCurve::OutCubic
            : QEasingCurve::InCubic);
    }
    _animation->start();

    emit clicked();
}

void Thumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == _toggle->orientation()) {
        const int s = height()-10;
        painter.drawEllipse(5+_offset, 5, s, s);
    } else {
        const int s = width()-10;
        painter.drawEllipse(5, 5+_offset, s, s);
    }
}

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      _thumb(new Thumb(this)),
      _overlay(new RippleOverlay(parent)),
      _orientation(Qt::Horizontal)
{
    setCheckable(true);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    CustomShadowEffect *effect = new CustomShadowEffect;
    effect->setDistance(0);
    effect->setBlurRadius(6);
    effect->setColor(QColor(100, 100, 100));

    _thumb->setGraphicsEffect(effect);
    _thumb->installEventFilter(this);

    connect(_thumb, SIGNAL(clicked()), this, SLOT(toggle()));
    connect(_thumb, SIGNAL(clicked()), this, SLOT(addRipple()));
    connect(_thumb, SIGNAL(progressChanged(qreal)), this, SLOT(updateOverlayGeometry()));
}

Toggle::~Toggle()
{
}

QSize Toggle::sizeHint() const
{
    return Qt::Horizontal == _orientation
        ? QSize(64, 48)
        : QSize(48, 64);
}

void Toggle::setOrientation(Qt::Orientation orientation)
{
    if (_orientation == orientation)
        return;
    _orientation = orientation;
}

void Toggle::addRipple()
{
    if (Qt::Horizontal == _orientation) {
        const int d = height()/2;
        const int w = _thumb->height()/2+10;
        _overlay->addRipple(QPoint(10+d, 20+d), w);
    } else {
        const int d = width()/2;
        const int w = _thumb->width()/2+10;
        _overlay->addRipple(QPoint(10+d, 20+d), w);
    }
}

void Toggle::updateOverlayGeometry()
{
    const int d = _thumb->offset();

    if (Qt::Horizontal == _orientation) {
        _overlay->setGeometry(geometry().adjusted(-10+d, -20, 10+d, 20));
    } else {
        _overlay->setGeometry(geometry().adjusted(-10, -20+d, 10, 20+d));
    }
}

bool Toggle::event(QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::ParentChange == type && parentWidget()) {
        _overlay->setParent(parentWidget());
    } else if (QEvent::Resize == type || QEvent::Move == type) {
        _overlay->setGeometry(geometry().adjusted(-10, -20, 10, 20));
    }
    return QAbstractButton::event(event);
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == _orientation) {
        const int h = height()/2;
        const QRect r(0, h/2, width(), h);
        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
    } else {
        const int w = width()/2;
        const QRect r(w/2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w/2-4, w/2-4);
    }
}
