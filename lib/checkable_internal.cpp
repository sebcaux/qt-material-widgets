#include "checkable_internal.h"
#include <QPainter>
#include <QGraphicsColorizeEffect>

CheckableIcon::CheckableIcon(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      _effect(new QGraphicsColorizeEffect),
      _icon(icon),
      _iconSize(24),
      _opacity(1.0)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    setGraphicsEffect(_effect);
}

CheckableIcon::~CheckableIcon()
{
}

void CheckableIcon::setColor(const QColor &color)
{
    if (_effect->color() == color)
        return;

    _effect->setColor(color);
    update();
}

QColor CheckableIcon::color() const
{
    return _effect->color();
}

void CheckableIcon::setIconSize(qreal size)
{
    _iconSize = size;
    update();
}

qreal CheckableIcon::iconSize() const
{
    return _iconSize;
}

void CheckableIcon::setOpacity(qreal opacity)
{
    _opacity = opacity;
    update();
}

qreal CheckableIcon::opacity() const
{
    return _opacity;
}

void CheckableIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

#ifdef DEBUG_LAYOUT
    QPainter debug(this);
    debug.drawRect(rect().adjusted(0, 0, -1, -1));
#endif

    if (0 == _iconSize)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setOpacity(_opacity);

    const qreal p = static_cast<qreal>((height())-_iconSize)/2;
    const qreal z = _iconSize/24;

    QTransform t;
    t.translate(p, p);
    t.scale(z, z);
    painter.setTransform(t);

    _icon.paint(&painter, QRect(0, 0, 24, 24));
}
