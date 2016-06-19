#include "dialog_internal.h"
#include <QPainter>
#include "dialog.h"

DialogWindow::DialogWindow(Dialog *parent)
    : QWidget(parent),
      dialog(parent)
{
}

DialogWindow::~DialogWindow()
{
}

void DialogWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    QRectF r(0, 0, 200, 200);
    r.moveCenter(rect().center());

    painter.drawRect(r);
}

