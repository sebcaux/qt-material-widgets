#ifndef MENUPLUSPROXY_H
#define MENUPLUSPROXY_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <cmath>

class MenuPlusProxy : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal xScale WRITE setXScale READ xScale)
    Q_PROPERTY(qreal yScale WRITE setYScale READ yScale)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    MenuPlusProxy(QWidget *source, QGraphicsDropShadowEffect *effect, QWidget *parent = 0);
    ~MenuPlusProxy();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    inline void setXScale(qreal sx);
    inline qreal xScale() const;

    inline void setYScale(qreal sy);
    inline qreal yScale() const;

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

signals:
    void expand();
    void collapse();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(MenuPlusProxy)

    QWidget                   *const m_source;
    QGraphicsDropShadowEffect *const m_effect;
    qreal                            m_sx;
    qreal                            m_sy;
    qreal                            m_opacity;
};

inline void MenuPlusProxy::setXScale(qreal sx)
{
    m_sx = sx;
    update();
    m_effect->update();
}

inline qreal MenuPlusProxy::xScale() const
{
    return m_sx;
}

inline void MenuPlusProxy::setYScale(qreal sy)
{
    m_sy = sy;
    update();
    m_effect->update();
}

inline qreal MenuPlusProxy::yScale() const
{
    return m_sy;
}

inline void MenuPlusProxy::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    const qreal alpha = 100*(pow(opacity, 5));
    m_effect->setColor(QColor(0, 0, 0, alpha));
    m_effect->update();
    update();
}

inline qreal MenuPlusProxy::opacity() const
{
    return m_opacity;
}

#endif // MENUPLUSPROXY_H
