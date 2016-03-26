#include <QAbstractButton>
#include <QDebug>
#include <QPainter>
#include "toggle.h"
#include "../lib/rippleoverlay.h"
#include "../lib/customshadoweffect.h"

Thumb::Thumb(QWidget *parent)
    : QWidget(parent)
{
}

Thumb::~Thumb()
{
}

void Thumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.drawRect(rect());

    const int d = qMin(width(), height());

    painter.drawEllipse(d, d, d/2, d/2);
}

Toggle::Toggle(QWidget *parent)
    : QAbstractButton(parent),
      _overlay(new RippleOverlay(this)),
      _thumb(new Thumb(this))
{
    CustomShadowEffect *effect = new CustomShadowEffect;
    _thumb->setGraphicsEffect(effect);
}

Toggle::~Toggle()
{
}

void Toggle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.setRenderHint(QPainter::Antialiasing);

    const int h = height()/2;

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(QRect(0, h-h/2, width(), h+h/2), h, h);
}
