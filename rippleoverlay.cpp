#include <QDebug>
#include <QPainter>
#include "rippleoverlay.h"
#include "ripple.h"

RippleOverlay::RippleOverlay(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

RippleOverlay::~RippleOverlay()
{
}

void RippleOverlay::addRipple(const QPoint &position, qreal radius)
{
    Ripple *ripple = new Ripple(position);
    ripple->setRadiusEndValue(radius);
    ripples.push_back(ripple);
    connect(ripple, SIGNAL(valueChanged()), this, SLOT(update()));
    connect(ripple, SIGNAL(finished()), this, SLOT(deleteRipple()));
    ripple->startAnimation();
}

void RippleOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    QList<Ripple *>::const_iterator i;
    for (i = ripples.begin(); i != ripples.end(); ++i)
    {
        const Ripple *ripple = *i;
        const qreal radius = ripple->radius();
        const QPointF &center = ripple->center();
        painter.setOpacity(ripple->opacity());
        painter.drawEllipse(center, radius, radius);
    }
}

void RippleOverlay::deleteRipple()
{
    if (ripples.isEmpty()) {
        qWarning() << "RippleOverlay::deleteRipple was called when no active ripple.";
        return;
    }
    ripples.takeFirst()->deleteLater();
}
