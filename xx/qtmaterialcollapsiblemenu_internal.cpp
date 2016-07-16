#include "xx/qtmaterialcollapsiblemenu_internal.h"
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QPainter>
#include "xx/qtmaterialcollapsiblemenu.h"

/*!
 *  \class QtMaterialCollapsibleMenuStateMachine
 *  \internal
 */

QtMaterialCollapsibleMenuStateMachine::QtMaterialCollapsibleMenuStateMachine(
        QtMaterialCollapsibleMenuProxy *proxy,
        QtMaterialCollapsibleMenu      *parent)
    : QStateMachine(parent),
      m_menu(parent),
      m_proxy(proxy),
      m_expandedState(new QState),
      m_collapsedState(new QState),
      m_expandXAnimation(new QPropertyAnimation(this)),
      m_expandYAnimation(new QPropertyAnimation(this)),
      m_collapseXAnimation(new QPropertyAnimation(this)),
      m_collapseYAnimation(new QPropertyAnimation(this))
{
    Q_ASSERT(parent);

    addState(m_expandedState);
    addState(m_collapsedState);
    setInitialState(m_collapsedState);

    QSignalTransition *transition;

    transition = new QSignalTransition(m_proxy, SIGNAL(expand()));
    transition->setTargetState(m_expandedState);
    m_collapsedState->addTransition(transition);

    m_expandXAnimation->setTargetObject(m_proxy);
    m_expandXAnimation->setPropertyName("xScale");
    m_expandXAnimation->setDuration(200);
    m_expandXAnimation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(m_expandXAnimation);

    m_expandYAnimation->setTargetObject(m_proxy);
    m_expandYAnimation->setPropertyName("yScale");
    m_expandYAnimation->setDuration(500);
    m_expandYAnimation->setEasingCurve(QEasingCurve::OutElastic);
    transition->addAnimation(m_expandYAnimation);

    transition = new QSignalTransition(m_proxy, SIGNAL(collapse()));
    transition->setTargetState(m_collapsedState);
    m_expandedState->addTransition(transition);

    m_collapseXAnimation->setTargetObject(m_proxy);
    m_collapseXAnimation->setPropertyName("xScale");
    m_collapseXAnimation->setDuration(400);
    m_collapseXAnimation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(m_collapseXAnimation);

    m_collapseYAnimation->setTargetObject(m_proxy);
    m_collapseYAnimation->setPropertyName("yScale");
    m_collapseYAnimation->setDuration(500);
    m_collapseYAnimation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(m_collapseYAnimation);

    m_expandedState->assignProperty(m_proxy, "xScale", 1);
    m_expandedState->assignProperty(m_proxy, "yScale", 1);
    m_expandedState->assignProperty(m_proxy, "opacity", 1);

    m_collapsedState->assignProperty(m_proxy, "xScale", 0.5);
    m_collapsedState->assignProperty(m_proxy, "yScale", 0.05);
    m_collapsedState->assignProperty(m_proxy, "opacity", 0);

    QPropertyAnimation *animation = new QPropertyAnimation(this);
    animation->setTargetObject(m_proxy);
    animation->setPropertyName("opacity");
    animation->setDuration(160);
    addDefaultAnimation(animation);

    connect(m_expandedState, SIGNAL(propertiesAssigned()),
            m_menu, SLOT(setOpaque()));
    connect(m_expandedState, SIGNAL(propertiesAssigned()),
            m_menu, SIGNAL(wasExpanded()));
    connect(m_collapsedState, SIGNAL(propertiesAssigned()),
            m_menu, SIGNAL(wasCollapsed()));
}

QtMaterialCollapsibleMenuStateMachine::~QtMaterialCollapsibleMenuStateMachine()
{
}

/*!
 *  \class QtMaterialCollapsibleMenuProxy
 *  \internal
 */

QtMaterialCollapsibleMenuProxy::QtMaterialCollapsibleMenuProxy(
        QWidget                   *source,
        QGraphicsDropShadowEffect *effect,
        QWidget                   *parent)
    : QWidget(parent),
      m_source(source),
      m_effect(effect),
      m_sx(0),
      m_sy(0),
      m_opacity(0)
{
}

QtMaterialCollapsibleMenuProxy::~QtMaterialCollapsibleMenuProxy()
{
}

QSize QtMaterialCollapsibleMenuProxy::sizeHint() const
{
    if (!m_source) {
        return QWidget::sizeHint();
    }
    return m_source->sizeHint();
}

void QtMaterialCollapsibleMenuProxy::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QRect r(rect());
    QPixmap pm = m_source->grab(r.translated(-m_source->pos())).scaled(
                static_cast<qreal>(r.width())*m_sx,
                static_cast<qreal>(r.height())*m_sy,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation);

    painter.setOpacity(m_opacity);
    painter.drawPixmap(0, 0, pm);
}
