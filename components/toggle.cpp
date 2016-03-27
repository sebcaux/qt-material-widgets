#include <QAbstractButton>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include "toggle.h"
#include "../lib/rippleoverlay.h"
#include "../lib/customshadoweffect.h"

Thumb::Thumb(Toggle *parent)
    : QWidget(parent),
      _toggle(parent),
      _animation(new QPropertyAnimation(this)),
      _progress(0),
      _offset(0)
{
    parent->installEventFilter(this);

    _animation->setPropertyName("progress");
    _animation->setTargetObject(this);
    _animation->setDuration(350);
    _animation->setStartValue(0);
    _animation->setEndValue(1);
}

Thumb::~Thumb()
{
}

void Thumb::setProgress(qreal p)
{
    if (_progress == p)
        return;

    _progress = p;
    _offset = p*(static_cast<qreal>(width()-qMin(width(), height())));

    emit progressChanged(p);

    update();
}

bool Thumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect().adjusted(9, 9, -9, -9));
    }
    return QWidget::eventFilter(obj, event);
}

void Thumb::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
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

    /*
    painter.save();
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawRect(rect());
    painter.restore();
    */

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

//    painter.drawEllipse(5 + _progress*(static_cast<qreal>(width()-d)), 5, d-10, d-10);

    const int d = qMin(width(), height());
    painter.drawEllipse(5 + _offset, 5, d-10, d-10);
}

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      _thumb(new Thumb(this)),
      _overlay(new RippleOverlay(parent))
{
    setFixedSize(64, 48);
    setCheckable(true);

    CustomShadowEffect *effect = new CustomShadowEffect;
    effect->setDistance(0);
    effect->setBlurRadius(6);
    effect->setColor(QColor(100, 100, 100));

    _thumb->setGraphicsEffect(effect);
    _thumb->installEventFilter(this);

    connect(_thumb, SIGNAL(clicked()), this, SLOT(toggle()));
    connect(_thumb, SIGNAL(clicked()), this, SLOT(xx()));
    connect(_thumb, SIGNAL(progressChanged(qreal)), this, SLOT(yy()));
}

Toggle::~Toggle()
{
}

void Toggle::xx()
{
    const int d = height()/2;                         // ???
    _overlay->addRipple(QPoint(10+d, 20+d), 35);
}

void Toggle::yy()
{
    //const int d = progress*(static_cast<qreal>(width()-d));

    //const int r = qMin(_thumb->width(), _thumb->height());
    const int d = _thumb->offset();

    _overlay->setGeometry(geometry().adjusted(-10+d, -20, 10+d, 20));
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

    painter.drawRect(rect());

    const int h = height()/2;

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    const QRect r(0, h-h/2, width(), h);
    painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
}
