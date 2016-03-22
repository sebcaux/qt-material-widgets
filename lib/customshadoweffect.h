/*
 * http://stackoverflow.com/questions/23718827/qt-shadow-around-window
 */
#ifndef CUSTOMSHADOWEFFECT_H
#define CUSTOMSHADOWEFFECT_H

#include <QGraphicsEffect>

class CustomShadowEffect : public QGraphicsEffect
{
    Q_OBJECT

    Q_PROPERTY(qreal distance WRITE setDistance READ distance)
    Q_PROPERTY(qreal blurRadius WRITE setBlurRadius READ blurRadius)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    explicit CustomShadowEffect(QObject *parent = 0);

    void draw(QPainter *painter);
    QRectF boundingRectFor(const QRectF &rect) const;

    inline void setDistance(qreal distance) { _distance = distance; updateBoundingRect(); }
    inline qreal distance() const { return _distance; }

    inline void setBlurRadius(qreal blurRadius) { _blurRadius = blurRadius; updateBoundingRect(); }
    inline qreal blurRadius() const { return _blurRadius; }

    inline void setColor(const QColor &color) { _color = color; }
    inline QColor color() const { return _color; }

private:
    qreal  _distance;
    qreal  _blurRadius;
    QColor _color;
};

#endif // CUSTOMSHADOWEFFECT_H
