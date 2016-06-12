#include "radiobutton.h"
#include <QPainter>
#include "radiobutton_p.h"

RadioButtonPrivate::RadioButtonPrivate(RadioButton *q)
    : q_ptr(q)
{
}

void RadioButtonPrivate::init()
{
    //Q_Q(RadioButton);
}

RadioButton::RadioButton(QWidget *parent)
    : QRadioButton(parent),
      d_ptr(new RadioButtonPrivate(this))
{
}

RadioButton::~RadioButton()
{
}

void RadioButton::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void RadioButton::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void RadioButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(rect());

    QWidget::paintEvent(event);
}
