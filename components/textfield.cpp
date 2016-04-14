#include <QWidget>
#include <QPainter>
#include "textfield.h"
#include "style.h"

TextField::TextField(QWidget *parent)
    : QLineEdit(parent)
{
    setStyle(&Style::instance());
}

TextField::~TextField()
{
}

void TextField::mousePressEvent(QMouseEvent *event)
{
    QLineEdit::mousePressEvent(event);
}

void TextField::mouseReleaseEvent(QMouseEvent *event)
{
    QLineEdit::mouseReleaseEvent(event);
}

void TextField::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter painter(this);
    painter.drawRect(0, 0, 50, 50);
}
