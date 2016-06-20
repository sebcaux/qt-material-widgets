#include "ripple.h"
#include "rippleoverlay.h"

Ripple::Ripple(const QPoint &center, RippleOverlay *overlay, QObject *parent)
    : QObject(parent),
      _overlay(overlay),
      _radiusAnimation(animate("radius")),
      _opacityAnimation(animate("opacity")),
      _radius(0),
      _opacity(0),
      _center(center)
{
    connect(&_group, SIGNAL(finished()), this, SIGNAL(finished()));

    setOpacityStartValue(0.5);
    setOpacityEndValue(0);
    setRadiusStartValue(0);
    setRadiusEndValue(300);

    _brush.setColor(Qt::black);
    _brush.setStyle(Qt::SolidPattern);
}

Ripple::~Ripple()
{
}

void Ripple::setOverlay(RippleOverlay *overlay)
{
    _overlay = overlay;
}

void Ripple::setRadius(qreal radius)
{
    Q_ASSERT(_overlay);

    if (radius == _radius)
        return;

    _radius = radius;
    _overlay->update();
}

void Ripple::setOpacity(qreal opacity)
{
    Q_ASSERT(_overlay);

    if (opacity == _opacity)
        return;

    _opacity = opacity;
    _overlay->update();
}

void Ripple::setColor(const QColor &color)
{
    if (color == _brush.color())
        return;

    _brush.setColor(color);
}

QPropertyAnimation *Ripple::animate(const QByteArray &property)
{
    QPropertyAnimation *animation = new QPropertyAnimation;
    animation->setPropertyName(property);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setTargetObject(this);
    animation->setDuration(800);
    _group.addAnimation(animation);
    return animation;
}
