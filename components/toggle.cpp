#include <QAbstractButton>
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include "toggle.h"
#include "../lib/rippleoverlay.h"
#include "../lib/customshadoweffect.h"

Thumb::Thumb(Toggle *parent)
    : QWidget(parent)
{
    parent->installEventFilter(this);
}

Thumb::~Thumb()
{
}

bool Thumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(parentWidget()->rect().adjusted(2, 2, -2, -2));
    }
    return QWidget::eventFilter(obj, event);
}

void Thumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    qDebug() << rect();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    QPen pen;
//    pen.setColor(Qt::red);
//    painter.setPen(pen);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(120, 120, 120));

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    const int d = qMin(width(), height());
    painter.drawEllipse(0, 0, d, d);
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
    painter.setRenderHint(QPainter::Antialiasing);

    const int h = height()/2;

    QBrush brush;
    brush.setColor(QColor(180, 180, 180));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(QRect(0, h-h/2, width(), h), h/2, h/2);
}
