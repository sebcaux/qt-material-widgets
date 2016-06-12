#include "radiobutton_internal.h"
#include <QPainter>
#include <QGraphicsColorizeEffect>

RadioButtonIcon::RadioButtonIcon(const QIcon &icon, QWidget *parent)
    : QWidget(parent),
      _icon(icon),
      _iconSize(24),
      _effect(new QGraphicsColorizeEffect)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    setGraphicsEffect(_effect);
}

RadioButtonIcon::~RadioButtonIcon()
{
}

void RadioButtonIcon::setColor(const QColor &color)
{
    _effect->setColor(color);
    update();
}

QColor RadioButtonIcon::color() const
{
    return _effect->color();
}

void RadioButtonIcon::setIconSize(int size)
{
    _iconSize = size;
    update();
}

int RadioButtonIcon::iconSize() const
{
    return _iconSize;
}

void RadioButtonIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

#ifdef DEBUG_LAYOUT
    QPainter debug(this);
    debug.drawRect(rect().adjusted(0, 0, -1, -1));
#endif

    if (0 == _iconSize)
        return;

    QPainter painter(this);

    const int p = (height() - _iconSize)/2;
    _icon.paint(&painter, QRect(p, p, _iconSize, _iconSize));
}
