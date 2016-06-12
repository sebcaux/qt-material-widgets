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

    inline void setClipping(bool enabled) { useClip = enabled; update(); }
    inline bool hasClipping() const { return useClip; }

    inline void setClipRegion(const QRegion &region) { clipRegion = region; update(); }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void deleteRipple();

private:
    QList<Ripple *> ripples;
    QRegion clipRegion;
    bool    useClip;
};

#endif // RIPPLEOVERLAY_H
