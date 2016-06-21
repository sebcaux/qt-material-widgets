#include "transparencyproxy_internal.h"
#include <QPainter>

ProxyWidget::ProxyWidget(QWidget *widget, QWidget *parent)
    : QWidget(parent),
      _widget(widget),
      _opacity(0)
{
}

ProxyWidget::~ProxyWidget()
{
}

void ProxyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setOpacity(_opacity);

    QPixmap pixmap = _widget->grab(rect());
    painter.drawPixmap(rect(), pixmap);

#ifdef DEBUG_LAYOUT
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);
    painter.setPen(pen);

    painter.drawRect(rect());
#endif
}
