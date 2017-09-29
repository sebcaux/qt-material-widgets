#include "components/menuplusproxy.h"
#include <QPainter>
#include <QPixmap>
#include <QEvent>
#include <QDebug>

MenuPlusProxy::MenuPlusProxy(QWidget *source, QGraphicsDropShadowEffect *effect, QWidget *parent)
    : QWidget(parent),
      m_source(source),
      m_effect(effect),
      m_sx(0),
      m_sy(0),
      m_opacity(0)
{
}

MenuPlusProxy::~MenuPlusProxy()
{
}

QSize MenuPlusProxy::sizeHint() const
{
    if (!m_source) {
        return QWidget::sizeHint();
    }
    return m_source->sizeHint();
}

void MenuPlusProxy::paintEvent(QPaintEvent *event)
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
