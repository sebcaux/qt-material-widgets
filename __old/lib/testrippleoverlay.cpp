#include "testrippleoverlay.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QDebug>

TestRippleOverlay::TestRippleOverlay(QWidget *parent)
    : QWidget(parent),
      _animation(new QPropertyAnimation(this)),
      _radius(0)
{
    _animation->setStartValue(0);
    _animation->setEndValue(200);
    _animation->setTargetObject(this);
    _animation->setPropertyName("radius");
    _animation->setDuration(300);
}

TestRippleOverlay::~TestRippleOverlay()
{
}

void TestRippleOverlay::setRadius(qreal radius)
{
    _radius = radius;

    refreshPixmap();
}

void TestRippleOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    //QBrush brush;
    //brush.setStyle(Qt::SolidPattern);
    //brush.setColor(Qt::black);
    //painter.setBrush(brush);
    //painter.setOpacity(0.5);
    //painter.setPen(Qt::NoPen);

    //painter.drawEllipse(_center, _radius, _radius);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setOpacity(1);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);

    painter.drawRect(rect());

    painter.drawPixmap(0, 0, _pixmap);
}

void TestRippleOverlay::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();

    _center = event->pos();
    _radius = 0;

    _animation->stop();
    _animation->start();
}

void TestRippleOverlay::refreshPixmap()
{
    _pixmap = QPixmap(size());
    _pixmap.fill(Qt::transparent);

    QPainter painter(&_pixmap);
    painter.initFrom(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.setOpacity(0.5);
    painter.setPen(Qt::NoPen);

    painter.drawEllipse(_center, _radius, _radius);

    update();
}
