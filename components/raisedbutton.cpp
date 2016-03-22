#include <QDebug>
#include <QPropertyAnimation>
#include <QStylePainter>
#include <QPaintEvent>
#include "raisedbutton.h"
#include "lib/customshadoweffect.h"

RaisedButton::RaisedButton(QWidget *parent)
    : FlatButton(parent)
{
    CustomShadowEffect *effect = new CustomShadowEffect;
    setGraphicsEffect(effect);
    setAutoFillBackground(true);

    QPropertyAnimation *animation;

    animation = new QPropertyAnimation;
    animation->setTargetObject(effect);
    animation->setPropertyName("distance");
    animation->setStartValue(effect->distance());
    animation->setEndValue(6);
    animation->setDuration(100);
    _group.addAnimation(animation);

    animation = new QPropertyAnimation;
    animation->setTargetObject(effect);
    animation->setPropertyName("blurRadius");
    animation->setStartValue(effect->blurRadius());
    animation->setEndValue(20);
    animation->setDuration(100);
    _group.addAnimation(animation);

    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(update()));
}

RaisedButton::~RaisedButton()
{
}

void RaisedButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    _group.setDirection(QAbstractAnimation::Forward);
    _group.start();

    FlatButton::mousePressEvent(event);
}

void RaisedButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    _group.setDirection(QAbstractAnimation::Backward);
    _group.start();

    FlatButton::mouseReleaseEvent(event);
}

void RaisedButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter painter(this);

    painter.drawControl(QStyle::CE_PushButton, getStyleOption());
}
