#include "qtmaterialswitch_internal.h"

#include "lib/qtmaterialripple.h"
#include "qtmaterialswitch.h"

#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include <QPainter>

/*!
 *  \class QtMaterialSwitchRippleOverlay
 *  \internal
 */

QtMaterialSwitchRippleOverlay::QtMaterialSwitchRippleOverlay(QtMaterialSwitchThumb *thumb, QtMaterialSwitchTrack *track, QtMaterialSwitch *parent)
    : QtMaterialRippleOverlay(parent->parentWidget()),
      m_switch(parent),
      m_thumb(thumb),
      m_track(track)
{
    connect(parent, &QAbstractButton::toggled, this, &QtMaterialSwitchRippleOverlay::addSwitchRipple);

    thumb->installEventFilter(this);
}

QtMaterialSwitchRippleOverlay::~QtMaterialSwitchRippleOverlay()
{
}

void QtMaterialSwitchRippleOverlay::addSwitchRipple()
{
    if (!m_switch->isEnabled())
    {
        return;
    }

    int w;
    if (m_switch->orientation() == Qt::Horizontal)
    {
        w = m_track->height() / 2 + 10;
    }
    else
    {
        w = m_track->width() / 2 + 10;
    }

    QtMaterialRipple *ripple = new QtMaterialRipple(QPoint(w, w + 10));
    ripple->setColor(m_track->trackColor());
    ripple->setRadiusEndValue(w);
    ripple->setOpacityStartValue(0.8);

    addRipple(ripple);
}

bool QtMaterialSwitchRippleOverlay::eventFilter(QObject *obj, QEvent *event)
{
    if (QEvent::Paint == event->type())
    {
        setGeometry(overlayGeometry());
        QList<QtMaterialRipple *> items = ripples();
        QColor color = m_track->trackColor();

        QList<QtMaterialRipple *>::const_iterator i;
        for (i = items.cbegin(); i != items.cend(); ++i)
        {
            (*i)->setColor(color);
        }
    }
    return QtMaterialRippleOverlay::eventFilter(obj, event);
}

QRect QtMaterialSwitchRippleOverlay::overlayGeometry() const
{
    const qreal offset = m_thumb->offset();
    if (Qt::Horizontal == m_switch->orientation())
    {
        return m_switch->geometry().adjusted(-10 + offset, -20, 10 + offset, 20);
    }

    return m_switch->geometry().adjusted(-10, -20 + offset, 10, 20 + offset);
}

/*!
 *  \class QtMaterialSwitchThumb
 *  \internal
 */

QtMaterialSwitchThumb::QtMaterialSwitchThumb(QtMaterialSwitch *parent)
    : QWidget(parent),
      m_switch(parent),
      m_shift(0),
      m_offset(0)
{
    Q_ASSERT(parent);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(6);
    effect->setColor(QColor(0, 0, 0, 80));
    effect->setOffset(QPointF(0, 1));
    setGraphicsEffect(effect);
}

QtMaterialSwitchThumb::~QtMaterialSwitchThumb()
{
}

void QtMaterialSwitchThumb::setShift(qreal shift)
{
    if (m_shift == shift)
    {
        return;
    }

    m_shift = shift;
    updateOffset();
}

void QtMaterialSwitchThumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(m_switch->isEnabled() ? m_thumbColor : Qt::white);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    int s;
    QRectF r;

    if (Qt::Horizontal == m_switch->orientation())
    {
        s = height() - 10;
        r = QRectF(5 + m_offset, 5, s, s);
    }
    else
    {
        s = width() - 10;
        r = QRectF(5, 5 + m_offset, s, s);
    }

    painter.drawEllipse(r);

    if (!m_switch->isEnabled())
    {
        brush.setColor(m_switch->disabledColor());
        painter.setBrush(brush);
        painter.drawEllipse(r);
    }
}

void QtMaterialSwitchThumb::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    updateOffset();
}

void QtMaterialSwitchThumb::updateOffset()
{
    const QSize s(Qt::Horizontal == m_switch->orientation() ? size() : size().transposed());
    m_offset = m_shift * static_cast<qreal>(s.width() - s.height());
    update();
}

/*!
 *  \class QtMaterialSwitchTrack
 *  \internal
 */

QtMaterialSwitchTrack::QtMaterialSwitchTrack(QtMaterialSwitch *parent)
    : QWidget(parent),
      m_switch(parent)
{
    Q_ASSERT(parent);
}

QtMaterialSwitchTrack::~QtMaterialSwitchTrack()
{
}

void QtMaterialSwitchTrack::setTrackColor(const QColor &color)
{
    m_trackColor = color;
    update();
}

void QtMaterialSwitchTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    if (m_switch->isEnabled())
    {
        brush.setColor(m_trackColor);
        painter.setOpacity(0.8);
    }
    else
    {
        brush.setColor(m_switch->disabledColor());
        painter.setOpacity(0.6);
    }
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == m_switch->orientation())
    {
        const int h = height() / 2;
        const QRect r(0, h / 2, width(), h);
        painter.drawRoundedRect(r.adjusted(14, 4, -14, -4), h / 2 - 4, h / 2 - 4);
    }
    else
    {
        const int w = width() / 2;
        const QRect r(w / 2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w / 2 - 4, w / 2 - 4);
    }
}
