#ifndef TESTRIPPLEOVERLAY_H
#define TESTRIPPLEOVERLAY_H

#include <QWidget>

class QPropertyAnimation;

class TestRippleOverlay : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal radius WRITE setRadius READ radius)

public:
    explicit TestRippleOverlay(QWidget *parent = 0);
    ~TestRippleOverlay();

    void setRadius(qreal radius);
    inline qreal radius() const { return _radius; }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void refreshPixmap();

private:
    Q_DISABLE_COPY(TestRippleOverlay)

    QPropertyAnimation *_animation;
    QPixmap             _pixmap;
    QPointF             _center;
    qreal               _radius;
};

#endif // TESTRIPPLEOVERLAY_H
