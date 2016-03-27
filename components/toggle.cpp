#include <QAbstractButton>
#include <QPropertyAnimation>
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
      _progress(0)
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

bool Thumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect().adjusted(9, 9, -9, -9));
    }
    return QWidget::eventFilter(obj, event);
}

void Thumb::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    emit clicked();

    if (_toggle->isChecked()) {
        _animation->setDirection(QAbstractAnimation::Forward);
        if (QAbstractAnimation::Running != _animation->state()) {
            _animation->setEasingCurve(QEasingCurve::OutCubic);
        }
    } else {
        _animation->setDirection(QAbstractAnimation::Backward);
        if (QAbstractAnimation::Running != _animation->state()) {
            _animation->setEasingCurve(QEasingCurve::InCubic);
        }
    }
    _animation->start();
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
    brush.setColor(QColor(120, 120, 120));

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    const int d = qMin(width(), height());
    painter.drawEllipse(5 + _progress*(static_cast<qreal>(width()-d)), 5, d-10, d-10);
}

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this)),
      _thumb(new Thumb(this))
{
    setCheckable(true);

    CustomShadowEffect *effect = new CustomShadowEffect;
    effect->setDistance(0);
    effect->setBlurRadius(6);
    effect->setColor(QColor(60, 60, 60));

    _thumb->setGraphicsEffect(effect);
    _thumb->installEventFilter(this);

    connect(_thumb, SIGNAL(clicked()), this, SLOT(toggle()));
}

Toggle::~Toggle()
{
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int h = height()/2;

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    const QRect r(0, h-h/2, width(), h);
    painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h/2-4, h/2-4);
}
