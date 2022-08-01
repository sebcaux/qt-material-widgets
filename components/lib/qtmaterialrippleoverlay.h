#ifndef QTMATERIALRIPPLEOVERLAY_H
#define QTMATERIALRIPPLEOVERLAY_H

#include "lib/qtmaterialoverlaywidget.h"

#include <QPainterPath>

class QtMaterialRipple;

class QtMaterialRippleOverlay : public QtMaterialOverlayWidget
{
    Q_OBJECT

public:
    explicit QtMaterialRippleOverlay(QWidget *parent = nullptr);
    ~QtMaterialRippleOverlay() override;

    void addRipple(QtMaterialRipple *ripple);
    void addRipple(const QPoint &position, qreal radius = 300);

    void removeRipple(QtMaterialRipple *ripple);

    inline void setClipping(bool enable);
    inline bool hasClipping() const;

    inline void setClipPath(const QPainterPath &path);

protected:
    void paintEvent(QPaintEvent *event) override;

    inline QList<QtMaterialRipple *> ripples() const;

private:
    Q_DISABLE_COPY(QtMaterialRippleOverlay)

    void paintRipple(QPainter *painter, QtMaterialRipple *ripple);

    QList<QtMaterialRipple *> m_ripples;
    QPainterPath m_clipPath;
    bool m_useClip;
};

inline void QtMaterialRippleOverlay::setClipping(bool enable)
{
    m_useClip = enable;
    update();
}

inline bool QtMaterialRippleOverlay::hasClipping() const
{
    return m_useClip;
}

inline void QtMaterialRippleOverlay::setClipPath(const QPainterPath &path)
{
    m_clipPath = path;
    update();
}

inline QList<QtMaterialRipple *> QtMaterialRippleOverlay::ripples() const
{
    return m_ripples;
}

#endif  // QTMATERIALRIPPLEOVERLAY_H
