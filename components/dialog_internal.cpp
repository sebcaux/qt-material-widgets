#include "dialog_internal.h"
#include <QPainter>
#include <QLayout>
#include "dialog.h"

DialogWindow::DialogWindow(Dialog *dialog, QWidget *parent)
    : QWidget(parent),
      dialog(dialog)
{
}

DialogWindow::~DialogWindow()
{
}

void DialogWindow::setOffset(int offset)
{
    QMargins margins = dialog->layout()->contentsMargins();
    margins.setBottom(offset);
    dialog->layout()->setContentsMargins(margins);
}

int DialogWindow::offset() const
{
    return dialog->layout()->contentsMargins().bottom();
}

void DialogWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);

    painter.drawRect(rect());
}
