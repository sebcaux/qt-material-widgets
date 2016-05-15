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

    _brush.setColor(Qt::black);
    _brush.setStyle(Qt::SolidPattern);
}

Ripple::~Ripple()
{
}

void Ripple::setRadius(qreal radius)
{
    if (radius == _radius)
        return;

    _radius = radius;
    emit changed();
}

void Ripple::setOpacity(qreal opacity)
{
    if (opacity == _opacity)
        return;

    _opacity = opacity;
    emit changed();
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
