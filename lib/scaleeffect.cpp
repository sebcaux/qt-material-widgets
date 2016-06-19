#include "scaleeffect.h"
#include <QPainter>

ScaleEffect::ScaleEffect(QObject *parent)
    : QGraphicsEffect(parent),
      _scaleX(1),
      _scaleY(1)
{
}

void ScaleEffect::setScale(qreal x, qreal y)
{
    _scaleX = x;
    _scaleY = y;
    updateBoundingRect();
}

QSizeF ScaleEffect::scale() const
{
    return QSizeF(_scaleX, _scaleY);
}

void ScaleEffect::draw(QPainter *painter)
{
    QPoint offset;
    const QPixmap pixmap = sourcePixmap(
                Qt::DeviceCoordinates,
                &offset,
                QGraphicsEffect::PadToEffectiveBoundingRect);

    const QSize &size = pixmap.size();
    painter->setWorldTransform(QTransform());
    painter->drawPixmap(offset, pixmap.scaled(
                            size.width()*_scaleX,
                            size.height()*_scaleY,
                            Qt::IgnoreAspectRatio,
                            Qt::SmoothTransformation));
}
