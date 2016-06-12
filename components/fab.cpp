#include "fab.h"
#include <QPainter>
#include <QDebug>
#include "fab_p.h"

FloatingActionButtonPrivate::FloatingActionButtonPrivate(FloatingActionButton *q)
    : RaisedButtonPrivate(q),
      mini(false)
{
}

FloatingActionButtonPrivate::~FloatingActionButtonPrivate()
{
}

void FloatingActionButtonPrivate::init()
{
    Q_Q(FloatingActionButton);

    q->setRole(Material::Primary);
}

FloatingActionButton::FloatingActionButton(QWidget *parent)
    : RaisedButton(parent)
{
    d_func()->init();
}

FloatingActionButton::~FloatingActionButton()
{
}

QSize FloatingActionButton::sizeHint() const
{
    Q_D(const FloatingActionButton);

    if (d->mini) {
        return QSize(40, 40);
    }
    return QSize(56, 56);
}

void FloatingActionButton::setMini(bool state)
{
    Q_D(FloatingActionButton);

    d->mini = state;
}

bool FloatingActionButton::isMini() const
{
    Q_D(const FloatingActionButton);

    return d->mini;
}

void FloatingActionButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    int s = qMin(width(), height());
    QRect square = QRect(0, 0, s, s);
    square.moveCenter(rect().center());

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(isEnabled()
       ? backgroundColor() : palette().color(QPalette::Disabled, QPalette::Background));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.drawEllipse(square);
}
