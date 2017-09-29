#ifndef SCALEEFFECT_H
#define SCALEEFFECT_H

#include <QGraphicsEffect>

class ScaleEffect : public QGraphicsEffect
{
    Q_OBJECT

public:
    explicit ScaleEffect(QObject *parent = 0);

    void setScale(qreal x, qreal y);
    QSizeF scale() const;
    inline qreal scaleX() const { return _scaleX; }
    inline qreal scaleY() const { return _scaleY; }

    void draw(QPainter *painter);

private:
    qreal _scaleX;
    qreal _scaleY;
};

#endif // SCALEEFFECT_H
