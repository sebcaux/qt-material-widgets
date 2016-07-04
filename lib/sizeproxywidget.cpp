#include "sizeproxywidget.h"
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QDebug>

SizeProxyWidget::SizeProxyWidget(QWidget *source, QWidget *parent)
    : QWidget(parent),
      m_sourceWidget(source),
      m_canvasSx(1.0),
      m_canvasSy(1.0),
      m_sx(1.0),
      m_sy(1.0),
      m_opacity(1.0)
{
    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Maximum);
    policy.setVerticalPolicy(QSizePolicy::Maximum);
    setSizePolicy(policy);

    //source->setParent(this, Qt::Tool);
    source->setParent(this);
    //source->installEventFilter(this);
}

SizeProxyWidget::~SizeProxyWidget()
{
}

QSize SizeProxyWidget::sizeHint() const
{
    return m_sourceWidget->sizeHint();
}

void SizeProxyWidget::setCanvasXScale(qreal s)
{
    m_canvasSx = s;
    update();
}

void SizeProxyWidget::setCanvasYScale(qreal s)
{
    m_canvasSy = s;
    update();
}

void SizeProxyWidget::setXScale(qreal s)
{
    m_sx = s;
    banan();
}

void SizeProxyWidget::setYScale(qreal s)
{
    m_sy = s;
    banan();
}

void SizeProxyWidget::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

bool SizeProxyWidget::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::Resize:
    {
        QPixmap pm = m_sourceWidget->grab(m_sourceWidget->geometry());
        m_pixmap = pm.scaled(static_cast<qreal>(m_sourceWidget->width())*m_sx,
                             static_cast<qreal>(m_sourceWidget->height())*m_sy,
                             Qt::IgnoreAspectRatio,
                             Qt::SmoothTransformation);
        break;
    }
    default:
        break;
    }
    return QWidget::event(event);
}

//bool SizeProxyWidget::eventFilter(QObject *obj, QEvent *event)
//{
//    qDebug() << event->type();
//    if (QEvent::Resize == event->type()) {
//        qDebug() << size();
//    }
//    if (QEvent::LayoutRequest == event->type()) {
//        qDebug() << height();
//        //m_pixmap = m_sourceWidget->grab(QRect(0, 0, 300, 480));
//    }
//    return QWidget::eventFilter(obj, event);
//}

void SizeProxyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //painter.drawPixmap(0, 0, m_pixmap);

    //QRect r(rect());
    //r.setWidth(static_cast<qreal>(width())*m_sx);
    //r.setHeight(static_cast<qreal>(height())*m_sy);

    //painter.setPen(Qt::green);

    //painter.setPen(Qt::NoPen);
    //painter.setBrush(Qt::blue);
    //painter.drawRect(rect());

    //painter.setOpacity(m_opacity);
    //painter.scale(m_sx, m_sy);

    painter.drawPixmap(0, 0, m_pixmap);
}

void SizeProxyWidget::banan()
{
    QRect rect(m_sourceWidget->geometry());
    rect.setWidth(static_cast<qreal>(rect.width())*m_sx);
    rect.setHeight(static_cast<qreal>(rect.height())*m_sy);
    setGeometry(rect);
    update();
}
