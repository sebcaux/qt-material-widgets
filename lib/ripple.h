#ifndef RIPPLE_H
#define RIPPLE_H

#include <QObject>
#include <QPoint>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QBrush>

class RippleOverlay;

class Ripple : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal radius WRITE setRadius READ radius)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    explicit Ripple(const QPoint &center, RippleOverlay *overlay = 0, QObject *parent = 0);
    ~Ripple();

    void setOverlay(RippleOverlay *overlay);

    void setRadius(qreal radius);
    inline qreal radius() const { return _radius; }

    void setOpacity(qreal opacity);
    inline qreal opacity() const { return _opacity; }

    void setColor(const QColor &color);
    inline QColor color() const { return _brush.color(); }

    inline void setBrush(const QBrush &brush) { _brush = brush; }
    inline QBrush brush() const { return _brush; }

    inline const QPoint &center() const { return _center; }

    inline void setDuration(int radius, int opacity)
    {
        _radiusAnimation->setDuration(radius);
        _opacityAnimation->setDuration(opacity);
    }

    inline void setDuration(int duration)
    {
        _radiusAnimation->setDuration(duration);
        _opacityAnimation->setDuration(duration);
    }

    inline void setEasingCurve(QEasingCurve radius, QEasingCurve opacity)
    {
        _radiusAnimation->setEasingCurve(radius);
        _opacityAnimation->setEasingCurve(opacity);
    }

    inline void setEasingCurve(QEasingCurve easing)
    {
        _radiusAnimation->setEasingCurve(easing);
        _opacityAnimation->setEasingCurve(easing);
    }

    inline void setOpacityStartValue(qreal value) { _opacityAnimation->setStartValue(value); }
    inline void setOpacityEndValue(qreal value) { _opacityAnimation->setEndValue(value); }
    inline void setRadiusStartValue(qreal value) { _radiusAnimation->setStartValue(value); }
    inline void setRadiusEndValue(qreal value) { _radiusAnimation->setEndValue(value); }

    inline void startAnimation() { _group.start(); }

signals:
    void finished();

private:
    QPropertyAnimation *animate(const QByteArray &property);

    QParallelAnimationGroup   _group;
    RippleOverlay            *_overlay;
    QPropertyAnimation *const _radiusAnimation;
    QPropertyAnimation *const _opacityAnimation;
    qreal                     _radius;
    qreal                     _opacity;
    QPoint                    _center;
    QBrush                    _brush;
};

#endif // RIPPLE_H
