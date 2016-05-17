#include "raisedbutton.h"
#include <QGraphicsDropShadowEffect>
#include "raisedbutton_p.h"

void RaisedButtonPrivate::init()
{
    Q_Q(RaisedButton);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(7);
    effect->setOffset(QPoint(0, 0));
    effect->setColor(QColor(0, 0, 0, 100));
    q->setGraphicsEffect(effect);

    q->setAutoFillBackground(true);
}

RaisedButton::RaisedButton(QWidget *parent)
    : FlatButton(*new RaisedButtonPrivate(this), parent)
{
    Q_D(RaisedButton);

    d->init();
}

RaisedButton::~RaisedButton()
{
}

//#include <QDebug>
//#include <QPropertyAnimation>
//#include <QGraphicsDropShadowEffect>
//#include <QStylePainter>
//#include <QPaintEvent>
//#include "raisedbutton.h"
//
//RaisedButton::RaisedButton(QWidget *parent)
//    : FlatButton(parent)
//{
//    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
//    effect->setBlurRadius(7);
//    effect->setOffset(QPoint(0, 0));
//    effect->setColor(QColor(0, 0, 0, 100));
//    setGraphicsEffect(effect);
//
//    setAutoFillBackground(true);
//
//    QPropertyAnimation *animation;
//
//    animation = new QPropertyAnimation;
//    animation->setTargetObject(effect);
//    animation->setPropertyName("offset");
//    animation->setStartValue(QPoint(0, 6));
//    animation->setEndValue(QPoint(0, 0));
//    animation->setDuration(100);
//    _group.addAnimation(animation);
//
//    animation = new QPropertyAnimation;
//    animation->setTargetObject(effect);
//    animation->setPropertyName("blurRadius");
//    animation->setStartValue(20);
//    animation->setEndValue(7);
//    animation->setDuration(100);
//    _group.addAnimation(animation);
//
//    connect(animation, SIGNAL(valueChanged(QVariant)), this, SLOT(update()));
//}
//
//RaisedButton::~RaisedButton()
//{
//}
//
//void RaisedButton::mousePressEvent(QMouseEvent *event)
//{
//    _group.setDirection(QAbstractAnimation::Backward);
//    _group.start();
//
//    FlatButton::mousePressEvent(event);
//}
//
//void RaisedButton::mouseReleaseEvent(QMouseEvent *event)
//{
//    _group.setDirection(QAbstractAnimation::Forward);
//    _group.start();
//
//    FlatButton::mouseReleaseEvent(event);
//}
//
//void RaisedButton::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//
//    QStylePainter painter(this);
//
////    painter.drawControl(QStyle::CE_PushButton, getStyleOption());
//}
//
