#include <QWidget>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionButton>
#include "checkbox.h"

Checkbox::Checkbox(QWidget *parent)
    : QAbstractButton(parent)
{
    setFixedSize(200, 200);
}

Checkbox::~Checkbox()
{
}

void Checkbox::mousePressEvent(QMouseEvent *event)
{
    QAbstractButton::mousePressEvent(event);
}

void Checkbox::mouseReleaseEvent(QMouseEvent *event)
{
    QAbstractButton::mouseReleaseEvent(event);
}

void Checkbox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter p(this);
    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawControl(QStyle::CE_CheckBox, opt);

    p.drawRect(rect().adjusted(0, 0, -1, -1));        // tmp
}

void Checkbox::initStyleOption(QStyleOptionButton *option) const
{
    if (!option)
        return;
    //Q_D(const QCheckBox);
    option->initFrom(this);
    /*
    if (d->down)
        option->state |= QStyle::State_Sunken;
    if (d->tristate && d->noChange)
        option->state |= QStyle::State_NoChange;
    else
        option->state |= d->checked ? QStyle::State_On : QStyle::State_Off;
    */
    if (testAttribute(Qt::WA_Hover) && underMouse()) {
        /*
        if (d->hovering)
            option->state |= QStyle::State_MouseOver;
        else
            option->state &= ~QStyle::State_MouseOver;
            */
    }
    option->text = "Label label";
    /*
    option->text = d->text;
    option->icon = d->icon;
    option->iconSize = iconSize();
    */
}
