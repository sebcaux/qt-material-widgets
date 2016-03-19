#include "ripple.h"

Ripple::Ripple(const QPoint &center, QObject *parent)
    : QObject(parent),
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
}

Ripple::~Ripple()
{
}

QPropertyAnimation *Ripple::animate(const QByteArray &property)
{
    QPropertyAnimation *animation = new QPropertyAnimation;
    animation->setPropertyName(property);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->setTargetObject(this);
    animation->setDuration(700);
    _group.addAnimation(animation);
    return animation;
}
