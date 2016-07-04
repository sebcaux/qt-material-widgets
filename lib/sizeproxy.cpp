#include "sizeproxy.h"
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QPushButton>

ProxyWidget2::ProxyWidget2(QWidget *source, QWidget *parent)
    : QWidget(parent),
      m_sourceWidget(source),
      m_sx(1.0),
      m_sy(1.0),
      m_scaled(false)
{
    //source->installEventFilter(this);
}

ProxyWidget2::~ProxyWidget2()
{
}

//QSize ProxyWidget2::sizeHint() const
//{
//    return m_sourceWidget->sizeHint();
//    //return QSize(500, 500);
//}

bool ProxyWidget2::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateLater:
    //case QEvent::Move:
    //case QEvent::Resize:
    {
        QRect rect(m_sourceWidget->geometry());
        //rect.setWidth(rect.width()*m_sx);
        //rect.setHeight(rect.height()*m_sy);
        setGeometry(rect);
        break;
    }
    default:
        break;
    }

    return QWidget::eventFilter(obj, event);
}

void ProxyWidget2::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    if (m_scaled) {
        painter.scale(m_sx, m_sy);
    }

    //qDebug() << rect();

    //m_sourceWidget->ensurePolished();

    //QPixmap pixmap = m_sourceWidget->grab(rect());

    QPixmap pixmap = m_sourceWidget->grab(rect());
    painter.drawPixmap(QRect(0, 0, 50, 100), pixmap);

    //painter.drawRect(m_sourceWidget->rect());
    painter.setPen(Qt::blue);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

SizeProxy::SizeProxy(QWidget *widget)
    : QStackedLayout(),
      m_proxy(new ProxyWidget2(widget))
{
    addWidget(widget);
    addWidget(m_proxy);

    //setCurrentIndex(0);

    //widget->setAttribute(Qt::WA_DontShowOnScreen);

    setStackingMode(QStackedLayout::StackAll);
    widget->setVisible(false);
}

SizeProxy::~SizeProxy()
{
}

void SizeProxy::setGeometry(const QRect &geometry)
{
    qDebug() << geometry;

    //setGeometry(500, 500);

    //QRect rect(m_sourceWidget->geometry());
    QRect rect(geometry);
    //rect.setWidth(rect.width()*m_proxy->m_sx);
    //rect.setHeight(rect.height()*m_proxy->m_sy);

    QStackedLayout::setGeometry(rect);
}

void SizeProxy::setScale(qreal sx, qreal sy)
{
    const bool scaled = !qFuzzyCompare(1.0, sx) || !qFuzzyCompare(1.0, sy);

    //if (1 != currentIndex() && scaled) {
    //    setCurrentIndex(1);
    //} else if (0 != currentIndex() && !scaled) {
    //    setCurrentIndex(0);
    //}

    m_proxy->m_scaled = scaled;
    m_proxy->m_sx = sx;
    m_proxy->m_sy = sy;
    m_proxy->update();
}

void SizeProxy::getScale(qreal *sx, qreal *sy)
{
    *sx = m_proxy->m_sx;
    *sy = m_proxy->m_sy;
}

void SizeProxy::setXScale(qreal s)
{
    setScale(s, m_proxy->m_sy);
}

qreal SizeProxy::xScale() const
{
    return m_proxy->m_sx;
}

void SizeProxy::setYScale(qreal s)
{
    setScale(m_proxy->m_sx, s);
}

qreal SizeProxy::yScale() const
{
    return m_proxy->m_sy;
}
