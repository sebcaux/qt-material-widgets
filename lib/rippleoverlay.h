#ifndef RIPPLEOVERLAY_H
#define RIPPLEOVERLAY_H

#include <QWidget>

class Ripple;

class RippleOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit RippleOverlay(QWidget *parent = 0);
    ~RippleOverlay();

    void addRipple(const QPoint &position, qreal radius = 300);
    void addRipple(Ripple *ripple);

    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void deleteRipple();

private:
    QList<Ripple *> ripples;
};

#endif // RIPPLEOVERLAY_H
