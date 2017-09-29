#include "rippleoverlay.h"
#include <QDebug>
#include <QPainter>
#include "ripple.h"

RippleOverlay::RippleOverlay(QWidget *parent)
    : QWidget(parent),
      useClip(false)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

RippleOverlay::~RippleOverlay()
{
}

void RippleOverlay::addRipple(const QPoint &position, qreal radius)
{
    Ripple *ripple = new Ripple(position, this);
    ripple->setRadiusEndValue(radius);
    addRipple(ripple);
}

void RippleOverlay::addRipple(Ripple *ripple)
{
    ripple->setOverlay(this);
    ripples.push_back(ripple);
    connect(ripple, SIGNAL(finished()), this, SLOT(deleteRipple()));
    ripple->startAnimation();
}

void RippleOverlay::setColor(const QColor &color)
{
    QList<Ripple *>::const_iterator i;
    for (i = ripples.begin(); i != ripples.end(); ++i)
        (*i)->setColor(color);
}

void RippleOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if (useClip) {
        painter.setClipPath(clipPath);
    }

    QList<Ripple *>::const_iterator i;
    for (i = ripples.begin(); i != ripples.end(); ++i)
    {
        const Ripple *ripple = *i;
        const qreal radius = ripple->radius();
        const QPointF &center = ripple->center();
        painter.setOpacity(ripple->opacity());
        painter.setBrush(ripple->brush());
        painter.drawEllipse(center, radius, radius);
    }

    QPen pen;
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    painter.setOpacity(1);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect());
}

void RippleOverlay::deleteRipple()
{
    if (ripples.isEmpty()) {
        qWarning() << "RippleOverlay::deleteRipple was called when no ripples were active.";
        return;
    }
    ripples.takeFirst()->deleteLater();
}
