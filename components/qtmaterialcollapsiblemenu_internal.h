#ifndef QTMATERIALCOLLAPSIBLEMENU_INTERNAL_H
#define QTMATERIALCOLLAPSIBLEMENU_INTERNAL_H

#include <QStateMachine>
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <cmath>

class QState;
class QPropertyAnimation;
class QtMaterialCollapsibleMenu;
class QtMaterialCollapsibleMenuProxy;

class QtMaterialCollapsibleMenuStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    QtMaterialCollapsibleMenuStateMachine(QtMaterialCollapsibleMenuProxy *proxy, QtMaterialCollapsibleMenu *parent);
    ~QtMaterialCollapsibleMenuStateMachine();

    inline QState *expandedState() const;
    inline QState *collapsedState() const;
    inline QPropertyAnimation *expandXAnimation() const;
    inline QPropertyAnimation *expandYAnimation() const;
    inline QPropertyAnimation *collapseXAnimation() const;
    inline QPropertyAnimation *collapseYAnimation() const;

private:
    Q_DISABLE_COPY(QtMaterialCollapsibleMenuStateMachine)

    QtMaterialCollapsibleMenu      *const m_menu;
    QtMaterialCollapsibleMenuProxy *const m_proxy;
    QState                         *const m_expandedState;
    QState                         *const m_collapsedState;
    QPropertyAnimation             *const m_expandXAnimation;
    QPropertyAnimation             *const m_expandYAnimation;
    QPropertyAnimation             *const m_collapseXAnimation;
    QPropertyAnimation             *const m_collapseYAnimation;
};

inline QState *QtMaterialCollapsibleMenuStateMachine::expandedState() const
{
    return m_expandedState;
}

inline QState *QtMaterialCollapsibleMenuStateMachine::collapsedState() const
{
    return m_collapsedState;
}

inline QPropertyAnimation *QtMaterialCollapsibleMenuStateMachine::expandXAnimation() const
{
    return m_expandXAnimation;
}

inline QPropertyAnimation *QtMaterialCollapsibleMenuStateMachine::expandYAnimation() const
{
    return m_expandYAnimation;
}

inline QPropertyAnimation *QtMaterialCollapsibleMenuStateMachine::collapseXAnimation() const
{
    return m_collapseXAnimation;
}

inline QPropertyAnimation *QtMaterialCollapsibleMenuStateMachine::collapseYAnimation() const
{
    return m_collapseYAnimation;
}

class QGraphicsDropShadowEffect;

class QtMaterialCollapsibleMenuProxy : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal xScale WRITE setXScale READ xScale)
    Q_PROPERTY(qreal yScale WRITE setYScale READ yScale)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)

public:
    QtMaterialCollapsibleMenuProxy(QWidget *source, QGraphicsDropShadowEffect *effect, QWidget *parent = 0);
    ~QtMaterialCollapsibleMenuProxy();

    QSize sizeHint() const Q_DECL_OVERRIDE;

    inline void setXScale(qreal sx);
    inline qreal xScale() const;

    inline void setYScale(qreal sy);
    inline qreal yScale() const;

    inline void setOpacity(qreal opacity);
    inline qreal opacity() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialCollapsibleMenuProxy)

    QWidget                   *const m_source;
    QGraphicsDropShadowEffect *const m_effect;
    qreal                            m_sx;
    qreal                            m_sy;
    qreal                            m_opacity;
};

inline void QtMaterialCollapsibleMenuProxy::setXScale(qreal sx)
{
    m_sx = sx;
    update();
    m_effect->update();
}

inline qreal QtMaterialCollapsibleMenuProxy::xScale() const
{
    return m_sx;
}

inline void QtMaterialCollapsibleMenuProxy::setYScale(qreal sy)
{
    m_sy = sy;
    update();
    m_effect->update();
}

inline qreal QtMaterialCollapsibleMenuProxy::yScale() const
{
    return m_sy;
}

inline void QtMaterialCollapsibleMenuProxy::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    m_effect->setColor(QColor(0, 0, 0, 100*(pow(opacity, 5))));
    m_effect->update();
    update();
}

inline qreal QtMaterialCollapsibleMenuProxy::opacity() const
{
    return m_opacity;
}

#endif // QTMATERIALCOLLAPSIBLEMENU_INTERNAL_H
