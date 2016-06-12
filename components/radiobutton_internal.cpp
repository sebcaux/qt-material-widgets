#include "radiobutton_internal.h"
#include <QPainter>

RadioButtonIcon::RadioButtonIcon(QWidget *parent)
    : QWidget(parent)
{
}

RadioButtonIcon::~RadioButtonIcon()
{
}

void RadioButtonIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    painter.setPen(Qt::red);
    painter.drawRect(rect());
}
